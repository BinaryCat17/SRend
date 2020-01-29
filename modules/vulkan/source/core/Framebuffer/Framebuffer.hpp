#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // FramebufferImpl --------------------------------------------------------------------------------------------------

  class FramebufferImpl
  {
   public:
    explicit FramebufferImpl(std::shared_ptr<DeviceImpl> device, FramebufferCreateFlags const& createFlags);

    FramebufferImpl(FramebufferImpl const&) = delete;

    FramebufferImpl(FramebufferImpl&&) = delete;

    FramebufferImpl& operator=(FramebufferImpl const&) = delete;

    FramebufferImpl& operator=(FramebufferImpl&&) = delete;

    ~FramebufferImpl()
    {
      vezDestroyFramebuffer(device_->getVkDevice(), vkFramebuffer_);
    }

    [[nodiscard]] VezFramebuffer getVkFramebuffer() const
    {
      return vkFramebuffer_;
    }

    void addAttachment(Image const& image);

    void setAttachment(utils::IndexT index, Image const& image);

    void removeAttachment(utils::IndexT index)
    {
      images_.erase(images_.begin() + index);
    }

    void update();

   private:
    std::shared_ptr<DeviceImpl> device_;
    std::vector<Image> images_;
    VezFramebuffer vkFramebuffer_ = nullptr;
    bool needUpdate_ = true;
  };
}  // namespace vulkan