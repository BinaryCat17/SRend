#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // RenderPassImpl ---------------------------------------------------------------------------------------------------

  class RenderPassImpl
  {
   public:
    explicit RenderPassImpl(std::shared_ptr<DeviceImpl> const&, RenderPassCreateFlags const&)
    {
    }

    RenderPassImpl(RenderPassImpl const&) = delete;

    RenderPassImpl(RenderPassImpl&&) = delete;

    RenderPassImpl& operator=(RenderPassImpl const&) = delete;

    RenderPassImpl& operator=(RenderPassImpl&&) = delete;

    [[nodiscard]] std::vector<VezAttachmentReference> const& getVkAttachments() const
    {
      return attachments_;
    }

    void addColorAttachment(std::array<float, 4> const& clearValue, AttachmentLoadOp loadOp, AttachmentStoreOp store);

    void addDepthAttachment(
        float depthClearValue, unsigned stencilClearValue, AttachmentLoadOp loadOp, AttachmentStoreOp store);

   private:
    std::vector<VezAttachmentReference> attachments_;
  };

}  // namespace vulkan