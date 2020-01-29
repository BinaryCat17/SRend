#include "Device.hpp"
#include "../PhysicalDevice/PhysicalDevice.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  std::vector<char const*> getVkDeviceExtensions(ExtensionsFlags const& extensions)
  {
    std::vector<char const*> result;

    if (extensions & ExtensionsFlagBits::Presentation)
    {
      result.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    }

    return result;
  }

  auto createVkDevice(DeviceCreateFlags const&, PhysicalDevice const& physicalDevice, ExtensionsFlags const& extensions)
  {
    auto vkExtensions = getVkDeviceExtensions(extensions);

    VezDeviceCreateInfo createInfo = {};
    createInfo.enabledExtensionCount = static_cast<uint32_t>(vkExtensions.size());
    createInfo.ppEnabledExtensionNames = vkExtensions.data();

    VkDevice vkDevice = nullptr;
    checkResult(vezCreateDevice(physicalDevice.getImpl()->getVkPhysicalDevice(), &createInfo, &vkDevice));
    return std::unique_ptr<VkDevice_T, decltype(vezDestroyDevice)*>(vkDevice, &vezDestroyDevice);
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

    BufferManager deviceLocalManager(device, allSupportedUsage, VEZ_MEMORY_GPU_ONLY, 100 * 1000 * 1000);
    BufferManager hostLocalManager(device, allSupportedUsage, VEZ_MEMORY_CPU_ONLY, 100 * 1000 * 1000);
    BufferManager hostToDeviceManager(device, allSupportedUsage, VEZ_MEMORY_CPU_TO_GPU, 100 * 1000 * 1000);
    BufferManager deviceToHostManager(device, allSupportedUsage, VEZ_MEMORY_GPU_TO_CPU, 100 * 1000 * 1000);
    BufferManager stagingManager(device, stagingUsage, VEZ_MEMORY_CPU_ONLY, 100 * 1000 * 1000);

    return DeviceBuffers{std::move(deviceLocalManager), std::move(hostLocalManager), std::move(hostToDeviceManager),
        std::move(deviceToHostManager), std::move(stagingManager)};
  }

  // DeviceImpl -------------------------------------------------------------------------------------------------------

  DeviceImpl::DeviceImpl(std::shared_ptr<ApplicationImpl> const& application, DeviceCreateFlags const& createFlags,
      PhysicalDevice const& physicalDevice)
      : application_(application),
        physicalDevice_(physicalDevice.getImpl()),
        vkDevice_(createVkDevice(createFlags, physicalDevice, application->getEnabledExtensions())),
        queues_(createQueues(vkDevice_.get())),
        buffers_(createBuffers(vkDevice_.get()))
  {
  }

  // Device -----------------------------------------------------------------------------------------------------------

  Device::Device(vulkan::Application const& application, vulkan::DeviceCreateFlags const& createFlags,
      vulkan::PhysicalDevice const& physicalDevice)
      : pimpl_(std::make_shared<DeviceImpl>(application.getImpl(), createFlags, physicalDevice))
  {
  }

}  // namespace vulkan
