#pragma once
#include "../Device/Device.hpp"

namespace vulkan::presentation
{
  // RenderWindowImpl -------------------------------------------------------------------------------------------------

  class RenderWindowImpl
  {
   public:
    RenderWindowImpl(std::shared_ptr<DeviceImpl> device, RenderWindowCreateFlags const& createFlags,
        wsystem::Window const& window, Format format, ColorSpace colorSpace);

    ~RenderWindowImpl();

    [[nodiscard]] std::shared_ptr<DeviceImpl> const& getDevice() const
    {
      return device_;
    }

    [[nodiscard]] Semaphore present(Image const& image, std::vector<WaitInfo> const& waitInfo);

   private:
    std::shared_ptr<DeviceImpl> device_;
    vk::SurfaceKHR vkSurface_;
    vk::Queue vkPresentationQueue_;
    VezSwapchain vkSwapchain_;
  };

}  // namespace vulkan