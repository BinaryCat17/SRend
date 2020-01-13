#include "Device.hpp"
#include "../Buffer/Buffer.hpp"
#include "../ColorBlendState/ColorBlendState.hpp"
#include "../CommandBuffer/CommandBuffer.hpp"
#include "../DepthStencilState/DepthStencilState.hpp"
#include "../Framebuffer/Framebuffer.hpp"
#include "../Image/Image.hpp"
#include "../InputAssemblyState/InputAssemblyState.hpp"
#include "../MultisampleState/MultisampleState.hpp"
#include "../PhysicalDevice/PhysicalDevice.hpp"
#include "../RasterizationState/RasterizationState.hpp"
#include "../RenderPass/RenderPass.hpp"
#include "../Sampler/Sampler.hpp"
#include "../Semaphore/Semaphore.hpp"
#include "../Shader/Shader.hpp"
#include "../ShaderState/ShaderState.hpp"
#include "../VertexInputState/VertexInputState.hpp"
#include "../ViewportState/ViewportState.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  VezMemoryFlags toVkMemoryFlags(MemoryType type)
  {
    switch (type)
    {
      case MemoryType::DeviceLocal:
        return VEZ_MEMORY_GPU_ONLY;
      case MemoryType::HostLocal:
        return VEZ_MEMORY_CPU_ONLY;
      case MemoryType::HostToDivice:
        return VEZ_MEMORY_CPU_TO_GPU;
      case MemoryType::DeviceToHost:
        return VEZ_MEMORY_GPU_TO_CPU;
    }
    throw std::runtime_error("undefined memory flags");
  }

  std::vector<char const*> getVkDeviceExtensions(ExtensionsFlags const& extensions)
  {
    std::vector<char const*> result;

    if (extensions & ExtensionsFlagBits::Presentation)
    {
      result.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    }

    return result;
  }

  vk::Device createVkDevice(
      DeviceCreateFlags const&, PhysicalDevice const& physicalDevice, ExtensionsFlags const& extensions)
  {
    auto vkExtensions = getVkDeviceExtensions(extensions);

    VezDeviceCreateInfo createInfo = {};
    createInfo.enabledExtensionCount = static_cast<uint32_t>(vkExtensions.size());
    createInfo.ppEnabledExtensionNames = vkExtensions.data();

    VkDevice vkDevice = nullptr;
    checkResult(vezCreateDevice(physicalDevice.getImpl()->getVkPhysicalDevice(), &createInfo, &vkDevice));
    return vkDevice;
  }

  DeviceQueues createQueues(vk::Device device)
  {
    DeviceQueues result;

    vezGetDeviceGraphicsQueue(device, 0, reinterpret_cast<VkQueue*>(&result.graphicQueue));
    vezGetDeviceComputeQueue(device, 0, reinterpret_cast<VkQueue*>(&result.computeQueue));
    vezGetDeviceTransferQueue(device, 0, reinterpret_cast<VkQueue*>(&result.transferQueue));

    return result;
  }

  DeviceBuffers createBuffers(vk::Device device)
  {
    vk::BufferUsageFlags allSupportedUsage =
        vk::BufferUsageFlagBits::eUniformBuffer | vk::BufferUsageFlagBits::eIndexBuffer |
        vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferSrc |
        vk::BufferUsageFlagBits::eTransferDst;
    vk::BufferUsageFlags stagingUsage = vk::BufferUsageFlagBits::eTransferSrc | vk::BufferUsageFlagBits::eTransferDst;

    BufferManager deviceLocalManager(device, allSupportedUsage, VEZ_MEMORY_GPU_ONLY, 100 * 1000 * 1000, {});
    BufferManager hostLocalManager(device, allSupportedUsage, VEZ_MEMORY_CPU_ONLY, 100 * 1000 * 1000, {});
    BufferManager hostToDeviceManager(device, allSupportedUsage, VEZ_MEMORY_CPU_TO_GPU, 100 * 1000 * 1000, {});
    BufferManager deviceToHostManager(device, allSupportedUsage, VEZ_MEMORY_GPU_TO_CPU, 100 * 1000 * 1000, {});
    BufferManager stagingManager(device, stagingUsage, VEZ_MEMORY_CPU_ONLY, 100 * 1000 * 1000, {});

    return DeviceBuffers{std::move(deviceLocalManager), std::move(hostLocalManager), std::move(hostToDeviceManager),
        std::move(deviceToHostManager), std::move(stagingManager)};
  }

  std::vector<VkCommandBuffer> toVkCommandBuffers(
      std::vector<std::pair<CommandBuffer, std::vector<WaitInfo>>> const& submitInfos)
  {
    std::vector<VkCommandBuffer> result;
    result.reserve(submitInfos.size());

    for (auto const& info : submitInfos)
    {
      result.push_back(info.first.getImpl()->getVkCommandBuffer());
    }

    return result;
  }

  std::vector<VkSemaphore> toVkSemaphores(
      std::vector<std::pair<CommandBuffer, std::vector<WaitInfo>>> const& submitInfos)
  {
    std::vector<VkSemaphore> result;

    for (auto const& info : submitInfos)
    {
      for (auto const& waitInfo : info.second)
      {
        result.push_back(waitInfo.semaphore.getImpl()->getVkSemaphore());
      }
    }

    return result;
  }

  std::vector<VkPipelineStageFlags> toVkWaitStages(
      std::vector<std::pair<CommandBuffer, std::vector<WaitInfo>>> const& submitInfos)
  {
    std::vector<VkPipelineStageFlags> result;

    for (auto const& info : submitInfos)
    {
      for (auto const& waitInfo : info.second)
      {
        result.push_back(static_cast<VkPipelineStageFlags>(waitInfo.waitStages));
      }
    }

    return result;
  }

  vk::Queue pickQueue(std::shared_ptr<DeviceImpl> const& device, CommandBufferType type)
  {
    switch (type)
    {
      case CommandBufferType::Transfer:
        return device->getQueues().transferQueue;
      case CommandBufferType::Graphic:
        return device->getQueues().graphicQueue;
      case CommandBufferType::Compute:
        return device->getQueues().computeQueue;
    }
    throw std::runtime_error("undefined queue");
  }

  // DeviceImpl -------------------------------------------------------------------------------------------------------

  DeviceImpl::DeviceImpl(std::shared_ptr<ApplicationImpl> const& application, DeviceCreateFlags const& createFlags,
      PhysicalDevice const& physicalDevice)
      : application_(application),
        vkDevice_(createVkDevice(createFlags, physicalDevice, application->getEnabledExtensions())),
        queues_(createQueues(vkDevice_)),
        buffers_(createBuffers(vkDevice_))
  {
  }

  DeviceImpl::~DeviceImpl()
  {
    vezDestroyDevice(vkDevice_);
  }

  // Device -----------------------------------------------------------------------------------------------------------

  std::vector<CommandBuffer> Device::createCommandBuffers(
      utils::SizeT count, CommandBufferCreateFlags const&, CommandBufferType type) const
  {
    VezCommandBufferAllocateInfo allocInfo = {};
    allocInfo.queue = pickQueue(pimpl_, type);
    allocInfo.commandBufferCount = static_cast<uint32_t>(count);

    std::vector<vk::CommandBuffer> vkCommandBuffers(count);
    checkResult(vezAllocateCommandBuffers(
        pimpl_->getVkDevice(), &allocInfo, reinterpret_cast<VkCommandBuffer*>(vkCommandBuffers.data())));

    std::vector<CommandBuffer> result;
    result.reserve(vkCommandBuffers.size());

    for (auto vkCommandBuffer : vkCommandBuffers)
    {
      result.emplace_back(std::make_shared<CommandBufferImpl>(pimpl_, vkCommandBuffer));
    }

    return result;
  }

  CommandBuffer Device::createCommandBuffer(CommandBufferCreateFlags const& createFlags, CommandBufferType type) const
  {
    return createCommandBuffers(1, createFlags, type).front();
  }

  std::vector<Semaphore> Device::submitCommandBuffers(
      std::vector<std::pair<CommandBuffer, std::vector<WaitInfo>>> const& submitInfos, CommandBufferType type) const
  {
    std::vector<vk::Semaphore> signalSemaphores(submitInfos.size());
    std::vector<VkCommandBuffer> commandBuffers = toVkCommandBuffers(submitInfos);
    std::vector<VkSemaphore> waitSemaphores = toVkSemaphores(submitInfos);
    std::vector<VkPipelineStageFlags> waitStages = toVkWaitStages(submitInfos);

    VezSubmitInfo vkSubmitInfo = {};
    vkSubmitInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());
    vkSubmitInfo.pCommandBuffers = commandBuffers.data();
    vkSubmitInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
    vkSubmitInfo.pWaitSemaphores = waitSemaphores.data();
    vkSubmitInfo.pWaitDstStageMask = waitStages.data();
    vkSubmitInfo.signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores.size());
    vkSubmitInfo.pSignalSemaphores = reinterpret_cast<VkSemaphore*>(signalSemaphores.data());

    VkFence waitFence = nullptr;
    checkResult(vezQueueSubmit(pickQueue(pimpl_, type), 1, &vkSubmitInfo, &waitFence));
    checkResult(vezWaitForFences(pimpl_->getVkDevice(), 1, &waitFence, true, UINT64_MAX));
    vezDestroyFence(pimpl_->getVkDevice(), waitFence);

    std::vector<Semaphore> result;
    result.reserve(signalSemaphores.size());

    for (auto const& semaphore : signalSemaphores)
    {
      result.emplace_back(std::make_shared<SemaphoreImpl>(semaphore));
    }

    return result;
  }

  Semaphore Device::submitCommandBuffer(
      CommandBuffer const& commandBuffer, std::vector<WaitInfo> const& waitInfos, CommandBufferType type) const
  {
    return submitCommandBuffers({{commandBuffer, waitInfos}}, type).front();
  }

  Buffer Device::createBuffer(BufferCreateFlags const& createFlags, MemoryType memoryType,
      BufferUsageFlags const& usage, utils::SizeT size, utils::AlignmentT alignment) const
  {
    return Buffer(std::make_shared<BufferImpl>(pimpl_, createFlags, memoryType, usage, size, alignment));
  }

  Image Device::createImage(ImageCreateFlags const& createFlags, Format format, ImageUsageFlags const& usage,
      utils::Extent3D const& extent, utils::SizeT mipLevelsCount, utils::SizeT arrayLayersCount,
      SampleCountFlagBits sampleCount, MemoryType memoryType) const
  {
    return Image(std::make_shared<BaseImage>(
        pimpl_, createFlags, format, usage, extent, mipLevelsCount, arrayLayersCount, sampleCount, memoryType));
  }

  Image Device::createImage(Image const& image, ImageSubResourceRange const& range,
      std::optional<Format> const& formatView, ComponentMapping const& components) const
  {
    return Image(std::make_shared<ViewImage>(pimpl_, image, range, formatView, components));
  }

  [[nodiscard]] Sampler Device::createSampler(SamplerCreateFlags createFlags) const
  {
    return Sampler(std::make_shared<SamplerImpl>(pimpl_, createFlags));
  }

  [[nodiscard]] Shader Device::createShader(ShaderCreateFlags createFlags) const
  {
    return Shader(std::make_shared<ShaderImpl>(pimpl_, createFlags));
  }

  [[nodiscard]] ShaderState Device::createShaderState(ShaderStateCreateFlags const& createFlags) const
  {
    return ShaderState(std::make_shared<ShaderStateImpl>(pimpl_, createFlags));
  }

  [[nodiscard]] VertexInputState Device::createVertexInputState(VertexInputStateCreateFlags const& createFlags) const
  {
    return VertexInputState(std::make_shared<VertexInputStateImpl>(pimpl_, createFlags));
  }

  [[nodiscard]] InputAssemblyState Device::createInputAssemblyState(
      InputAssemblyStateCreateFlags const& createFlags) const
  {
    return InputAssemblyState(std::make_shared<InputAssemblyStateImpl>(pimpl_, createFlags));
  }

  [[nodiscard]] RasterizationState Device::createRasterizationState(
      RasterizationStateCreateFlags const& createFlags) const
  {
    return RasterizationState(std::make_shared<RasterizationStateImpl>(pimpl_, createFlags));
  }

  [[nodiscard]] MultisampleState Device::createMultisampleState(MultisampleStateCreateFlags const& createFlags) const
  {
    return MultisampleState(std::make_shared<MultisampleStateImpl>(pimpl_, createFlags));
  }

  [[nodiscard]] DepthStencilState Device::createDepthStencilState(DepthStencilStateCreateFlags const& createFlags) const
  {
    return DepthStencilState(std::make_shared<DepthStencilStateImpl>(pimpl_, createFlags));
  }

  [[nodiscard]] ColorBlendState Device::createColorBlendState(ColorBlendStateCreateFlags const& createFlags) const
  {
    return ColorBlendState(std::make_shared<ColorBlendStateImpl>(pimpl_, createFlags));
  }

  [[nodiscard]] ViewportState Device::createViewportState(ViewportStateCreateFlags const& createFlags) const
  {
    return ViewportState(std::make_shared<ViewportStateImpl>(pimpl_, createFlags));
  }

  [[nodiscard]] RenderPass Device::createRenderPass(RenderPassCreateFlags const& createFlags) const
  {
    return RenderPass(std::make_shared<RenderPassImpl>(pimpl_, createFlags));
  }

  [[nodiscard]] Framebuffer Device::createFramebuffer(
      FramebufferCreateFlags const& createFlags, std::vector<Image> const& images) const
  {
    return Framebuffer(std::make_shared<FramebufferImpl>(pimpl_, createFlags, images));
  }

}  // namespace vulkan
