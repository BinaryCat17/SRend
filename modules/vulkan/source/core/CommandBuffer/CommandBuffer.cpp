#include "CommandBuffer.hpp"
#include "../Buffer/Buffer.hpp"
#include "../ColorBlendState/ColorBlendState.hpp"
#include "../DepthStencilState/DepthStencilState.hpp"
#include "../Framebuffer/Framebuffer.hpp"
#include "../Image/Image.hpp"
#include "../InputAssemblyState/InputAssemblyState.hpp"
#include "../MultisampleState/MultisampleState.hpp"
#include "../RasterizationState/RasterizationState.hpp"
#include "../RenderPass/RenderPass.hpp"
#include "../Sampler/Sampler.hpp"
#include "../Semaphore/Semaphore.hpp"
#include "../ShaderState/ShaderState.hpp"
#include "../VertexInputState/VertexInputState.hpp"
#include "../ViewportState/ViewportState.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  VkCommandBufferUsageFlags toVkCommandBufferUsageFlags(CommandBufferBeginFlags const& usage)
  {
    VkCommandBufferUsageFlags result = 0;

    if (usage & CommandBufferBeginFlagBits::OneTimeSubmit)
    {
      result |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    }
    if (usage & CommandBufferBeginFlagBits::SimultaneousUse)
    {
      result |= VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
    }

    return result;
  }

  std::vector<VkCommandBuffer> toVkCommandBuffers(
      std::vector<std::pair<CommandBuffer, std::vector<WaitInfo>>> const& submitInfos)
  {
    std::vector<VkCommandBuffer> result;
    result.reserve(submitInfos.size());

    for (auto const& info : submitInfos)
    {
      info.first.getImpl()->endRenderPass();
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

  // CommandBufferImpl ------------------------------------------------------------------------------------------------

  CommandBufferImpl::CommandBufferImpl(
      std::shared_ptr<DeviceImpl> device, vk::CommandBuffer vkCommandBuffer, vk::Queue queue)
      : device_(std::move(device)), vkCommandBuffer_(vkCommandBuffer), queue_(queue)
  {
  }

  CommandBufferImpl::~CommandBufferImpl()
  {
    vezFreeCommandBuffers(device_->getVkDevice(), 1, reinterpret_cast<VkCommandBuffer*>(&vkCommandBuffer_));
  }

  void CommandBufferImpl::begin(CommandBufferBeginFlags const& beginFlags)
  {
    vezBeginCommandBuffer(vkCommandBuffer_, toVkCommandBufferUsageFlags(beginFlags));
  }

  void CommandBufferImpl::beginRender(Framebuffer const& framebuffer, RenderPass const& renderPass)
  {
    framebuffer.getImpl()->update();
    VezRenderPassBeginInfo beginInfo = {};
    beginInfo.pAttachments = renderPass.getImpl()->getVkAttachments().data();
    beginInfo.attachmentCount = static_cast<uint32_t>(renderPass.getImpl()->getVkAttachments().size());
    beginInfo.framebuffer = framebuffer.getImpl()->getVkFramebuffer();

    vezCmdBeginRenderPass(&beginInfo);
    inRenderPass_ = true;
  }

  void CommandBufferImpl::setShaderState(ShaderState const& state)
  {
    state.getImpl()->update();
    vezCmdBindPipeline(state.getImpl()->getVkPipeline());
  }

  void CommandBufferImpl::setVertexInputState(VertexInputState const& state)
  {
    state.getImpl()->update();
    vezCmdSetVertexInputFormat(state.getImpl()->getVkVertexInputFormat());
  }

  void CommandBufferImpl::setInputAssemblyState(InputAssemblyState const& state)
  {
    vezCmdSetInputAssemblyState(&state.getImpl()->getVkInputAssemblyState());
  }

  void CommandBufferImpl::setRasterizationState(RasterizationState const& state)
  {
    vezCmdSetRasterizationState(&state.getImpl()->getVkRasterizationState());
  }

  void CommandBufferImpl::setMultisampleState(MultisampleState const& state)
  {
    vezCmdSetMultisampleState(&state.getImpl()->getVkMultisampleState());
  }

  void CommandBufferImpl::setDepthStencilState(DepthStencilState const& state)
  {
    vezCmdSetDepthStencilState(&state.getImpl()->getVkDepthStencilState());
  }

  void CommandBufferImpl::setViewportState(ViewportState const& state)
  {
    state.getImpl()->update();

    auto vkViewports = state.getImpl()->getVkViewports();
    auto vkScissors = state.getImpl()->getVkScissors();

    vezCmdSetViewport(
        0, static_cast<uint32_t>(vkScissors.size()), reinterpret_cast<VkViewport const*>(vkViewports.data()));
    vezCmdSetScissor(0, static_cast<uint32_t>(vkScissors.size()), reinterpret_cast<VkRect2D const*>(vkScissors.data()));
    vezCmdSetViewportState(static_cast<uint32_t>(vkViewports.size()));
  }

  void CommandBufferImpl::setColorBlendState(ColorBlendState const& state)
  {
    state.getImpl()->update();
    vezCmdSetColorBlendState(&state.getImpl()->getVkColorBlendState());
  }

  void CommandBufferImpl::draw(
      utils::IndexT firstVertex, utils::SizeT vertexCount, utils::IndexT firstInstance, utils::SizeT instanceCount)
  {
    vezCmdDraw(static_cast<uint32_t>(vertexCount), static_cast<uint32_t>(instanceCount),
        static_cast<uint32_t>(firstVertex), static_cast<uint32_t>(firstInstance));
  }

  void CommandBufferImpl::drawIndexed(utils::IndexT firstIndex, utils::SizeT indexCount, utils::IndexT firstInstance,
      utils::SizeT instanceCount, utils::OffsetT vertexOffset)
  {
    vezCmdDrawIndexed(static_cast<uint32_t>(indexCount), static_cast<uint32_t>(instanceCount),
        static_cast<uint32_t>(firstIndex), static_cast<int32_t>(vertexOffset), static_cast<uint32_t>(firstInstance));
  }

  void CommandBufferImpl::copyBuffer(Buffer const& srcBuffer, utils::OffsetT srcOffset, Buffer const& dstBuffer,
      utils::OffsetT dstOffset, utils::SizeT size)
  {
    auto const& srcBufferImpl = srcBuffer.getImpl();
    auto const& dstBufferImpl = dstBuffer.getImpl();

    VezBufferCopy range = {};
    range.size = size;
    range.srcOffset = srcBufferImpl->offset() + srcOffset;
    range.dstOffset = dstBufferImpl->offset() + dstOffset;

    vezCmdCopyBuffer(srcBufferImpl->getVkBuffer(), dstBufferImpl->getVkBuffer(), 1, &range);
  }

  void CommandBufferImpl::copyImage(Image const& srcImage, utils::Offset3D const& srcOffset,
      ImageSubResourceRange const& srcSubResource, Image const& dstImage, utils::Offset3D const& dstOffset,
      ImageSubResourceRange const& dstSubResource, utils::Extent3D const& extent)
  {
    VezImageCopy range = {};
    range.extent = toVkExtent(extent);
    range.srcOffset = toVkOffset(srcOffset);
    range.dstOffset = toVkOffset(dstOffset);
    range.srcSubresource = {static_cast<uint32_t>(srcSubResource.baseMipLevel),
        static_cast<uint32_t>(srcSubResource.baseArrayLayer), static_cast<uint32_t>(srcSubResource.arrayLayerCount)};
    range.dstSubresource = {static_cast<uint32_t>(dstSubResource.baseMipLevel),
        static_cast<uint32_t>(dstSubResource.baseArrayLayer), static_cast<uint32_t>(dstSubResource.arrayLayerCount)};

    for (auto i = static_cast<uint32_t>(dstSubResource.baseMipLevel); i != dstSubResource.mipLevelCount; ++i)
    {
      vezCmdCopyImage(srcImage.getImpl()->getVkImage(), dstImage.getImpl()->getVkImage(), 1, &range);

      ++range.srcSubresource.mipLevel;
    }
  }

  void CommandBufferImpl::copyBufferToImage(Buffer const& buffer, utils::OffsetT bufferOffset,
      utils::SizeT bufferRowLength, utils::SizeT bufferImageHeight, Image const& image,
      ImageSubResourceRange const& imageSubResource, utils::Offset3D const& imageOffset,
      utils::Extent3D const& imageExtent)
  {
    VezBufferImageCopy range = {};
    range.bufferOffset = buffer.getImpl()->offset() + bufferOffset;
    range.bufferImageHeight = static_cast<uint32_t>(bufferImageHeight);
    range.bufferRowLength = static_cast<uint32_t>(bufferRowLength);
    range.imageExtent = toVkExtent(imageExtent);
    range.imageOffset = toVkOffset(imageOffset);
    range.imageSubresource = {static_cast<uint32_t>(imageSubResource.baseMipLevel),
        static_cast<uint32_t>(imageSubResource.baseArrayLayer),
        static_cast<uint32_t>(imageSubResource.arrayLayerCount)};

    for (auto i = static_cast<uint32_t>(imageSubResource.baseMipLevel); i != imageSubResource.mipLevelCount; ++i)
    {
      vezCmdCopyBufferToImage(buffer.getImpl()->getVkBuffer(), image.getImpl()->getVkImage(), 1, &range);

      ++range.imageSubresource.mipLevel;
    }
  }

  void CommandBufferImpl::bindBuffer(Buffer const& buffer, BindingInfo const& bindingInfo)
  {
    auto const& bufferImpl = buffer.getImpl();

    vezCmdBindBuffer(bufferImpl->getVkBuffer(), bufferImpl->offset(), buffer.getSize(),
        static_cast<uint32_t>(bindingInfo.set), static_cast<uint32_t>(bindingInfo.binding),
        static_cast<uint32_t>(bindingInfo.index));
  }

  void CommandBufferImpl::bindImage(Image const& image, Sampler const& sampler, BindingInfo const& bindingInfo)
  {
    sampler.getImpl()->update();
    vezCmdBindImageView(image.getImpl()->getVkImageView(), sampler.getImpl()->getVkSampler(),
        static_cast<uint32_t>(bindingInfo.set), static_cast<uint32_t>(bindingInfo.binding),
        static_cast<uint32_t>(bindingInfo.index));
  }

  void CommandBufferImpl::bindVertexBuffer(Buffer const& buffer)
  {
    VkBuffer vkBuffer = buffer.getImpl()->getVkBuffer();
    VkDeviceSize offset = buffer.getImpl()->offset();
    vezCmdBindVertexBuffers(0, 1, &vkBuffer, &offset);
  }

  void CommandBufferImpl::bindIndexBuffer(Buffer const& buffer, IndexType indexType)
  {
    vezCmdBindIndexBuffer(
        buffer.getImpl()->getVkBuffer(), buffer.getImpl()->offset(), static_cast<VkIndexType>(indexType));
  }

  // CommandBuffer ----------------------------------------------------------------------------------------------------

  void CommandBuffer::begin(CommandBufferBeginFlags const& beginFlags)
  {
    pimpl_->begin(beginFlags);
  }

  void CommandBuffer::beginRender(Framebuffer const& framebuffer, RenderPass const& renderPass)
  {
    pimpl_->beginRender(framebuffer, renderPass);
  }

  void CommandBuffer::copyBuffer(Buffer const& srcBuffer, utils::OffsetT srcOffset, Buffer const& dstBuffer,
      utils::OffsetT dstOffset, utils::SizeT size)
  {
    pimpl_->copyBuffer(srcBuffer, srcOffset, dstBuffer, dstOffset, size);
  }

  void CommandBuffer::copyBuffer(Buffer const& srcBuffer, Buffer const& dstBuffer)
  {
    copyBuffer(srcBuffer, 0, dstBuffer, 0, srcBuffer.getSize());
  }

  void CommandBuffer::copyImage(Image const& srcImage, utils::Offset3D const& srcOffset,
      ImageSubResourceRange const& srcSubResource, Image const& dstImage, utils::Offset3D const& dstOffset,
      ImageSubResourceRange const& dstSubResource, utils::Extent3D const& extent)
  {
    pimpl_->copyImage(srcImage, srcOffset, srcSubResource, dstImage, dstOffset, dstSubResource, extent);
  }

  void CommandBuffer::copyImage(Image const& srcImage, utils::Offset3D const& srcOffset, Image const& dstImage,
      utils::Offset3D const& dstOffset, utils::Extent3D const& extent)
  {
    copyImage(srcImage, srcOffset, srcImage.getSubResourceRange(), dstImage, dstOffset, dstImage.getSubResourceRange(),
        extent);
  }

  void CommandBuffer::copyImage(Image const& srcImage, Image const& dstImage)
  {
    copyImage(srcImage, {}, srcImage.getSubResourceRange(), dstImage, {}, dstImage.getSubResourceRange(),
        srcImage.getExtent());
  }

  void CommandBuffer::copyBufferToImage(Buffer const& buffer, utils::OffsetT bufferOffset, utils::SizeT bufferRowLength,
      utils::SizeT bufferImageHeight, Image const& image, ImageSubResourceRange const& imageSubResource,
      utils::Offset3D const& imageOffset, utils::Extent3D const& imageExtent)
  {
    pimpl_->copyBufferToImage(
        buffer, bufferOffset, bufferRowLength, bufferImageHeight, image, imageSubResource, imageOffset, imageExtent);
  }

  void CommandBuffer::copyBufferToImage(Buffer const& buffer, utils::OffsetT bufferOffset, Image const& image,
      utils::Offset3D const& imageOffset, utils::Extent3D const& imageExtent)
  {
    copyBufferToImage(buffer, bufferOffset, 0, 0, image, image.getSubResourceRange(), imageOffset, imageExtent);
  }

  void CommandBuffer::copyBufferToImage(Buffer const& buffer, Image const& image)
  {
    copyBufferToImage(buffer, 0, 0, 0, image, image.getSubResourceRange(), {}, image.getExtent());
  }

  void CommandBuffer::draw(
      utils::IndexT firstVertex, utils::SizeT vertexCount, utils::IndexT firstInstance, utils::SizeT instanceCount)
  {
    pimpl_->draw(firstVertex, vertexCount, firstInstance, instanceCount);
  }

  void CommandBuffer::drawIndexed(utils::IndexT firstIndex, utils::SizeT indexCount, utils::IndexT firstInstance,
      utils::SizeT instanceCount, utils::OffsetT vertexOffset)
  {
    pimpl_->drawIndexed(firstIndex, indexCount, firstInstance, instanceCount, vertexOffset);
  }

  void CommandBuffer::bindBuffer(Buffer const& buffer, BindingInfo const& bindingInfo)
  {
    pimpl_->bindBuffer(buffer, bindingInfo);
  }

  void CommandBuffer::bindImage(Image const& image, Sampler const& sampler, BindingInfo const& bindingInfo)
  {
    pimpl_->bindImage(image, sampler, bindingInfo);
  }

  void CommandBuffer::setShaderState(ShaderState const& state)
  {
    pimpl_->setShaderState(state);
  }

  void CommandBuffer::setVertexInputState(VertexInputState const& state)
  {
    pimpl_->setVertexInputState(state);
  }

  void CommandBuffer::setInputAssemblyState(InputAssemblyState const& state)
  {
    pimpl_->setInputAssemblyState(state);
  }

  void CommandBuffer::setRasterizationState(RasterizationState const& state)
  {
    pimpl_->setRasterizationState(state);
  }

  void CommandBuffer::setMultisampleState(MultisampleState const& state)
  {
    pimpl_->setMultisampleState(state);
  }

  void CommandBuffer::setDepthStencilState(DepthStencilState const& state)
  {
    pimpl_->setDepthStencilState(state);
  }

  void CommandBuffer::setViewportState(ViewportState const& state)
  {
    pimpl_->setViewportState(state);
  }

  void CommandBuffer::setColorBlendState(ColorBlendState const& state)
  {
    pimpl_->setColorBlendState(state);
  }

  void CommandBuffer::bindVertexBuffer(Buffer const& buffer)
  {
    pimpl_->bindVertexBuffer(buffer);
  }

  void CommandBuffer::bindIndexBuffer(Buffer const& buffer, IndexType indexType)
  {
    pimpl_->bindIndexBuffer(buffer, indexType);
  }

  CommandBuffer::CommandBuffer(
      Device const& device, CommandBufferCreateFlags const& createFlags, CommandBufferType type)
  {
    *this = createCommandBuffers(device, 1, createFlags, type).front();
  }

  Semaphore CommandBuffer::submit(std::vector<WaitInfo> const& waitInfos)
  {
    pimpl_->endRenderPass();
    vezEndCommandBuffer();
    return submitCommandBuffers(Device(pimpl_->getDevice()), {{*this, waitInfos}}).front();
  }

  std::vector<CommandBuffer> createCommandBuffers(
      Device const& device, utils::SizeT count, CommandBufferCreateFlags const&, CommandBufferType type)
  {
    VezCommandBufferAllocateInfo allocInfo = {};
    allocInfo.queue = pickQueue(device.getImpl(), type);
    allocInfo.commandBufferCount = static_cast<uint32_t>(count);

    std::vector<vk::CommandBuffer> vkCommandBuffers(count);
    checkResult(vezAllocateCommandBuffers(
        device.getImpl()->getVkDevice(), &allocInfo, reinterpret_cast<VkCommandBuffer*>(vkCommandBuffers.data())));

    std::vector<CommandBuffer> result;
    result.reserve(vkCommandBuffers.size());

    for (auto vkCommandBuffer : vkCommandBuffers)
    {
      result.emplace_back(std::make_shared<CommandBufferImpl>(device.getImpl(), vkCommandBuffer, allocInfo.queue));
    }

    return result;
  }

  std::vector<Semaphore> submitCommandBuffers(
      Device const& device, std::vector<std::pair<CommandBuffer, std::vector<WaitInfo>>> const& submitInfos)
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

    auto const& deviceImpl = device.getImpl();

    VkFence waitFence = nullptr;
    checkResult(vezQueueSubmit(submitInfos.front().first.getImpl()->getVkQueue(), 1, &vkSubmitInfo, &waitFence));
    checkResult(vezWaitForFences(deviceImpl->getVkDevice(), 1, &waitFence, true, UINT64_MAX));
    vezDestroyFence(deviceImpl->getVkDevice(), waitFence);

    std::vector<Semaphore> result;
    result.reserve(signalSemaphores.size());

    for (auto const& semaphore : signalSemaphores)
    {
      result.emplace_back(std::make_shared<SemaphoreImpl>(semaphore));
    }

    return result;
  }

}  // namespace vulkan