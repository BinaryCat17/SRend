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

  void RenderPassImpl::addColorAttachment(
      std::array<float, 4> const& clearValue, AttachmentLoadOp loadOp, AttachmentStoreOp store)
  {
    VezAttachmentReference attachment = {};
    attachment.storeOp = toVkAttachmentStoreOp(store);
    attachment.loadOp = toVkAttachmentLoadOp(loadOp);
    attachment.clearValue.color = {{clearValue[0], clearValue[1], clearValue[2], clearValue[3]}};

    attachments_.push_back(attachment);
  }

  void RenderPassImpl::addDepthAttachment(
      float depthClearValue, unsigned stencilClearValue, AttachmentLoadOp loadOp, AttachmentStoreOp store)
  {
    VezAttachmentReference attachment = {};
    attachment.storeOp = toVkAttachmentStoreOp(store);
    attachment.loadOp = toVkAttachmentLoadOp(loadOp);
    attachment.clearValue.depthStencil = {VkClearDepthStencilValue{depthClearValue, stencilClearValue}};

    attachments_.push_back(attachment);
  }

  // RenderPass -------------------------------------------------------------------------------------------------------

  void RenderPass::addColorAttachment(
      std::array<float, 4> const& clearValue, AttachmentLoadOp loadOp, AttachmentStoreOp store)
  {
    pimpl_->addColorAttachment(clearValue, loadOp, store);
  }

  void RenderPass::addDepthAttachment(
      float depthClearValue, unsigned stencilClearValue, AttachmentLoadOp loadOp, AttachmentStoreOp store)
  {
    pimpl_->addDepthAttachment(depthClearValue, stencilClearValue, loadOp, store);
  }

}  // namespace vulkan