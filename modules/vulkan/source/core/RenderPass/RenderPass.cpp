#include "RenderPass.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  VkAttachmentLoadOp toVkAttachmentLoadOp(AttachmentLoadOp op)
  {
    return static_cast<VkAttachmentLoadOp>(op);
  }

  VkAttachmentStoreOp toVkAttachmentStoreOp(AttachmentStoreOp op)
  {
    return static_cast<VkAttachmentStoreOp>(op);
  }

  // RenderPassImpl ---------------------------------------------------------------------------------------------------

  void RenderPassImpl::addAttachment(std::variant<ColorClearValue, DepthClearValue> const& clearValue,
      AttachmentLoadOp loadOp, AttachmentStoreOp store)
  {
    attachments_.push_back({});
    setAttachment(attachments_.size() - 1, clearValue, loadOp, store);
  }

  void RenderPassImpl::setAttachment(utils::IndexT index,
      std::variant<ColorClearValue, DepthClearValue> const& clearValue, AttachmentLoadOp loadOp,
      AttachmentStoreOp store)
  {
    VezAttachmentReference attachment = {};
    attachment.storeOp = toVkAttachmentStoreOp(store);
    attachment.loadOp = toVkAttachmentLoadOp(loadOp);
    std::visit(
        [&attachment]<typename T>(T const& val) {
          if constexpr (std::is_same_v<T, ColorClearValue>)
          {
            attachment.clearValue.color = {
                {val.clearValue[0], val.clearValue[1], val.clearValue[2], val.clearValue[3]}};
          }
          else
          {
            attachment.clearValue.depthStencil.depth = val.depthClearValue;
            attachment.clearValue.depthStencil.stencil = val.stencilClearValue;
          }
        },
        clearValue);

    attachments_[index] = attachment;
  }

  // RenderPass -------------------------------------------------------------------------------------------------------

  RenderPass::RenderPass(Device const& device, RenderPassCreateFlags const& createFlags)
      : pimpl_(std::make_shared<RenderPassImpl>(device.getImpl(), createFlags))
  {
  }

  void RenderPass::addAttachment(std::variant<ColorClearValue, DepthClearValue> const& clearValue,
      AttachmentLoadOp loadOp, AttachmentStoreOp store)
  {
    pimpl_->addAttachment(clearValue, loadOp, store);
  }

  void RenderPass::setAttachment(utils::IndexT index, std::variant<ColorClearValue, DepthClearValue> const& clearValue,
      AttachmentLoadOp loadOp, AttachmentStoreOp store)
  {
    pimpl_->setAttachment(index, clearValue, loadOp, store);
  }

  void RenderPass::removeAttachment(utils::IndexT index)
  {
    pimpl_->removeAttachment(index);
  }

}  // namespace vulkan