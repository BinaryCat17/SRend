#include "CommandBufferImpl.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  VkStencilOp toVkStencilOp(StencilOp op)
  {
    switch (op)
    {
      case StencilOp::Keep:
        return VK_STENCIL_OP_KEEP;
      case StencilOp::Zero:
        return VK_STENCIL_OP_ZERO;
      case StencilOp::Replace:
        return VK_STENCIL_OP_REPLACE;
      case StencilOp::IncrementAndClamp:
        return VK_STENCIL_OP_INCREMENT_AND_CLAMP;
      case StencilOp::DecrementAndClamp:
        return VK_STENCIL_OP_DECREMENT_AND_CLAMP;
      case StencilOp::Invert:
        return VK_STENCIL_OP_INVERT;
      case StencilOp::IncrementAndWrap:
        return VK_STENCIL_OP_INCREMENT_AND_WRAP;
      case StencilOp::DecrementAndWrap:
        return VK_STENCIL_OP_DECREMENT_AND_WRAP;
    }
  }

  VkCompareOp toVkCompareOp(CompareOp op)
  {
    switch (op)
    {
      case CompareOp::Never:
        return VK_COMPARE_OP_NEVER;
      case CompareOp::Less:
        return VK_COMPARE_OP_LESS;
      case CompareOp::Equal:
        return VK_COMPARE_OP_EQUAL;
      case CompareOp::LessOrEqual:
        return VK_COMPARE_OP_LESS_OR_EQUAL;
      case CompareOp::Greater:
        return VK_COMPARE_OP_GREATER;
      case CompareOp::NotEqual:
        return VK_COMPARE_OP_NOT_EQUAL;
      case CompareOp::GreaterOrEqual:
        return VK_COMPARE_OP_GREATER_OR_EQUAL;
      case CompareOp::Always:
        return VK_COMPARE_OP_ALWAYS;
    }
  }

  VezStencilOpState toVkStencilOpState(StencilOpInfo const& info)
  {
    return {toVkStencilOp(info.failOp), toVkStencilOp(info.passOp), toVkStencilOp(info.depthFailOp),
        toVkCompareOp(info.compareOp)};
  }

  VkCommandBufferUsageFlags toVkCommandBufferUsageFlags(CommandBufferUsageFlags const& usage)
  {
    VkCommandBufferUsageFlags result = 0;

    if (usage & CommandBufferUsageFlagBits::OneTimeSubmit)
    {
      result |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    }
    if (usage & CommandBufferUsageFlagBits::SimultaneousUse)
    {
      result |= VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
    }

    return result;
  }

  std::vector<VkViewport> toVkViewports(std::vector<ViewportState> const& viewportInfos)
  {
    std::vector<VkViewport> result;
    result.reserve(viewportInfos.size());

    for (auto const& viewportInfo : viewportInfos)
    {
      result.push_back(VkViewport{viewportInfo.viewport.x(), viewportInfo.viewport.y(), viewportInfo.viewport.width(),
          viewportInfo.viewport.height(), viewportInfo.viewport.minDepth(), viewportInfo.viewport.maxDepth()});
    }

    return result;
  }

  std::vector<VkRect2D> toVkScissors(std::vector<ViewportState> const& viewportInfos)
  {
    std::vector<VkRect2D> result;
    result.reserve(viewportInfos.size());

    for (auto const& viewportInfo : viewportInfos)
    {
      result.push_back(VkRect2D{
          VkOffset2D{static_cast<int32_t>(viewportInfo.scissor.x()), static_cast<int32_t>(viewportInfo.scissor.y())},
          VkExtent2D{viewportInfo.scissor.width(), viewportInfo.scissor.height()}});
    }

    return result;
  }

  void cmdCopyBuffers(std::vector<BufferCopyInfo> const& copyInfos)
  {
    for (auto const& info : copyInfos)
    {
      auto srcBuffer = implCast<BufferImpl>(info.srcBuffer);
      auto dstBuffer = implCast<BufferImpl>(info.dstBuffer);

      VezBufferCopy range = {};
      range.size = info.size;
      range.srcOffset = srcBuffer->offset() + info.srcOffset;
      range.dstOffset = dstBuffer->offset() + info.dstOffset;

      vezCmdCopyBuffer(srcBuffer->getVkBuffer(), dstBuffer->getVkBuffer(), 1, &range);
    }
  }

  // BaseCommandBufferImpl --------------------------------------------------------------------------------------------

  BaseCommandBufferImpl::BaseCommandBufferImpl(Device device, vk::CommandBuffer vkCommandBuffer)
      : device_(std::move(device)), vkCommandBuffer_(vkCommandBuffer)
  {
  }

  BaseCommandBufferImpl::~BaseCommandBufferImpl()
  {
    vezFreeCommandBuffers(device_.getImpl()->getVkDevice(), 1, reinterpret_cast<VkCommandBuffer*>(&vkCommandBuffer_));
  }

  void BaseCommandBufferImpl::begin(CommandBufferUsageFlags const& usage)
  {
    checkResult(vezBeginCommandBuffer(vkCommandBuffer_, toVkCommandBufferUsageFlags(usage)));
  }

  // TransferCommandBufferImpl ----------------------------------------------------------------------------------------

  // buffer

  void TransferCommandBufferImpl::copyBuffers(std::vector<BufferCopyInfo> const& copyInfos)
  {
    cmdCopyBuffers(copyInfos);
  }

  void TransferCommandBufferImpl::copyBuffer(std::shared_ptr<Buffer> const& srcBuffer, utils::OffsetT srcOffset,
      std::shared_ptr<Buffer> const& dstBuffer, utils::OffsetT dstOffset, utils::SizeT size)
  {
    copyBuffers({{srcBuffer, srcOffset, dstBuffer, dstOffset, size}});
  }

  void TransferCommandBufferImpl::copyBuffer(
      std::shared_ptr<Buffer> const& srcBuffer, std::shared_ptr<Buffer> const& dstBuffer)
  {
    copyBuffer(srcBuffer, 0, dstBuffer, 0, srcBuffer->size());
  }

  // ComputeCommandBufferImpl -----------------------------------------------------------------------------------------

  // GraphicCommandBufferImpl -----------------------------------------------------------------------------------------

  // render

  void GraphicCommandBufferImpl::draw(
      utils::IndexT firstVertex, utils::SizeT vertexCount, utils::IndexT firstInstance, utils::SizeT instanceCount)
  {
    vezCmdDraw(static_cast<uint32_t>(vertexCount), static_cast<uint32_t>(instanceCount),
        static_cast<uint32_t>(firstVertex), static_cast<uint32_t>(firstInstance));
  }

  void GraphicCommandBufferImpl::drawIndexed(utils::IndexT firstIndex, utils::SizeT indexCount,
      utils::IndexT firstInstance, utils::SizeT instanceCount, utils::OffsetT vertexOffset)
  {
    vezCmdDrawIndexed(static_cast<uint32_t>(indexCount), static_cast<uint32_t>(instanceCount),
        static_cast<uint32_t>(firstIndex), static_cast<int32_t>(vertexOffset), static_cast<uint32_t>(firstInstance));
  }

  void GraphicCommandBufferImpl::setViewportState(std::vector<ViewportState> const& viewports)
  {
    auto vkViewports = toVkViewports(viewports);
    auto vkScissors = toVkScissors(viewports);

    vezCmdSetViewport(0, static_cast<uint32_t>(viewports.size()), vkViewports.data());
    vezCmdSetScissor(0, static_cast<uint32_t>(vkScissors.size()), vkScissors.data());
    vezCmdSetViewportState(static_cast<uint32_t>(viewports.size()));
  }

  void GraphicCommandBufferImpl::setDepthStencilState(
      std::optional<DepthState> const& depthState, std::optional<StencilState> const& stencilState)
  {
    VezDepthStencilState info = {};
    info.depthTestEnable = depthState.has_value();
    if (info.depthTestEnable)
    {
      info.depthWriteEnable = depthState->writeEnable;
      info.depthCompareOp = static_cast<VkCompareOp>(depthState->compareOp);
      info.depthBoundsTestEnable = depthState->boundsTestEnable;
    }

    info.stencilTestEnable = stencilState.has_value();
    if (info.stencilTestEnable)
    {
      info.front = toVkStencilOpState(stencilState->front);
      info.back = toVkStencilOpState(stencilState->back);
    }

    vezCmdSetDepthStencilState(&info);
  }

  // buffer

  void GraphicCommandBufferImpl::copyBuffers(std::vector<BufferCopyInfo> const& copyInfos)
  {
    cmdCopyBuffers(copyInfos);
  }

  void GraphicCommandBufferImpl::copyBuffer(std::shared_ptr<Buffer> const& srcBuffer, utils::OffsetT srcOffset,
      std::shared_ptr<Buffer> const& dstBuffer, utils::OffsetT dstOffset, utils::SizeT size)
  {
    copyBuffers({{srcBuffer, srcOffset, dstBuffer, dstOffset, size}});
  }

  void GraphicCommandBufferImpl::copyBuffer(
      std::shared_ptr<Buffer> const& srcBuffer, std::shared_ptr<Buffer> const& dstBuffer)
  {
    copyBuffer(srcBuffer, 0, dstBuffer, 0, srcBuffer->size());
  }

  void GraphicCommandBufferImpl::bindBuffers(
      std::vector<std::pair<std::shared_ptr<Buffer>, BindingInfo>> const& buffersBindingInfos)
  {
    for (auto const& info : buffersBindingInfos)
    {
      auto bufferImpl = implCast<BufferImpl>(info.first);

      vezCmdBindBuffer(bufferImpl->getVkBuffer(), bufferImpl->offset(), bufferImpl->offset(), info.second.set,
          info.second.binding, info.second.index);
    }
  }

  void GraphicCommandBufferImpl::bindBuffer(std::shared_ptr<Buffer> const& buffer, BindingInfo const& bindingInfo)
  {
    bindBuffers({{buffer, bindingInfo}});
  }

}  // namespace vulkan