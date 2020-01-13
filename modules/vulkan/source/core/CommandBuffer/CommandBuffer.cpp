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

  // CommandBufferImpl ------------------------------------------------------------------------------------------------

  CommandBufferImpl::CommandBufferImpl(std::shared_ptr<DeviceImpl> device, vk::CommandBuffer vkCommandBuffer)
      : device_(std::move(device)), vkCommandBuffer_(vkCommandBuffer)
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

  void CommandBufferImpl::end()
  {
    vezEndCommandBuffer();
  }

  void CommandBufferImpl::beginRender(Framebuffer const& framebuffer, RenderPass const& renderPass)
  {
    VezRenderPassBeginInfo beginInfo = {};
    beginInfo.pAttachments = renderPass.getImpl()->getVkAttachments().data();
    beginInfo.attachmentCount = static_cast<uint32_t>(renderPass.getImpl()->getVkAttachments().size());
    beginInfo.framebuffer = framebuffer.getImpl()->getVkFramebuffer();

    vezCmdBeginRenderPass(&beginInfo);
  }

  void CommandBufferImpl::endRender()
  {
    vezCmdEndRenderPass();
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

    for (uint32_t i = dstSubResource.baseMipLevel; i != dstSubResource.mipLevelCount; ++i)
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
    range.bufferOffset = bufferOffset;
    range.bufferImageHeight = static_cast<uint32_t>(bufferImageHeight);
    range.bufferRowLength = static_cast<uint32_t>(bufferRowLength);
    range.imageExtent = toVkExtent(imageExtent);
    range.imageOffset = toVkOffset(imageOffset);
    range.imageSubresource = {static_cast<uint32_t>(imageSubResource.baseMipLevel),
        static_cast<uint32_t>(imageSubResource.baseArrayLayer),
        static_cast<uint32_t>(imageSubResource.arrayLayerCount)};

    for (uint32_t i = imageSubResource.baseMipLevel; i != imageSubResource.mipLevelCount; ++i)
    {
      vezCmdCopyBufferToImage(buffer.getImpl()->getVkBuffer(), image.getImpl()->getVkImage(), 1, &range);

      ++range.imageSubresource.mipLevel;
    }
  }

  void CommandBufferImpl::bindBuffer(Buffer const& buffer, BindingInfo const& bindingInfo)
  {
    auto const& bufferImpl = buffer.getImpl();

    vezCmdBindBuffer(bufferImpl->getVkBuffer(), bufferImpl->offset(), buffer.getSize(), bindingInfo.set,
        bindingInfo.binding, bindingInfo.index);
  }

  void CommandBufferImpl::bindImage(Image const& image, Sampler const& sampler, BindingInfo const& bindingInfo)
  {
    vezCmdBindImageView(image.getImpl()->getVkImageView(), sampler.getImpl()->getVkSampler(), bindingInfo.set,
        bindingInfo.binding, bindingInfo.index);
  }

  // CommandBuffer ----------------------------------------------------------------------------------------------------

  void CommandBuffer::begin(CommandBufferBeginFlags const& beginFlags)
  {
    pimpl_->begin(beginFlags);
  }

  void CommandBuffer::end()
  {
    pimpl_->end();
  }

  void CommandBuffer::beginRender(Framebuffer const& framebuffer, RenderPass const& renderPass)
  {
    pimpl_->beginRender(framebuffer, renderPass);
  }

  void CommandBuffer::endRender()
  {
    pimpl_->endRender();
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

}  // namespace vulkan