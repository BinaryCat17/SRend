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

    void addAttachment(std::variant<ColorClearValue, DepthClearValue> const& clearValue,
                       AttachmentLoadOp loadOp = AttachmentLoadOp::Clear, AttachmentStoreOp store = AttachmentStoreOp::Store);

    void setAttachment(utils::IndexT index, std::variant<ColorClearValue, DepthClearValue> const& clearValue,
                       AttachmentLoadOp loadOp = AttachmentLoadOp::Clear, AttachmentStoreOp store = AttachmentStoreOp::Store);

    void removeAttachment(utils::IndexT index)
    {
      attachments_.erase(attachments_.begin() + index);
    }

   private:
    std::vector<VezAttachmentReference> attachments_;
  };

}  // namespace vulkan