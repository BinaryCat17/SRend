#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // FramebufferImpl --------------------------------------------------------------------------------------------------

  class FramebufferImpl
  {
   public:
    explicit FramebufferImpl(std::shared_ptr<DeviceImpl> device, FramebufferCreateFlags const& createFlags,
        std::vector<Image> const& images);

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

   private:
    std::shared_ptr<DeviceImpl> device_;
    VezFramebuffer vkFramebuffer_;
  };
}  // namespace vulkan