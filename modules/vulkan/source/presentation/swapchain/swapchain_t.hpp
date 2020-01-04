#pragma once
#include "../../core/Device/DeviceImpl.hpp"
#include "../../core/Image/ImageImpl.hpp"
#include "../../core/Queue/QueueImpl.hpp"
#include "../surface/surface_t.hpp"
#include "swapchain.hpp"

namespace vulkan
{
  // swapchain_t ------------------------------------------------------------------------------------------

  class swapchain_t
  {
   public:
    swapchain_t(device device, surface surface, vk::SurfaceFormatKHR format);

    ~swapchain_t()
    {
      vezDestroySwapchain(device_->get_vk_device(), vk_swapchain);
    }

    device get_device() const
    {
      return device_;
    }

    vk::SurfaceFormatKHR get_format() const
    {
      return format_;
    }

    VezSwapchain get_vk_swapchain() const
    {
      return vk_swapchain;
    }

   private:
    device device_;
    vk::SurfaceFormatKHR format_;
    VezSwapchain vk_swapchain;
  };
}  // namespace vulkan