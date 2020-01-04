#include "swapchain_t.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------

  VezSwapchain create_vk_swapchain(device device, surface surface, vk::SurfaceFormatKHR format)
  {
    VezSwapchainCreateInfo create_info = {};
    create_info.format = format;
    create_info.surface = surface->get_vk_surface();
    create_info.tripleBuffer = true;

    VezSwapchain swapchain_ = nullptr;
    check_result(vezCreateSwapchain(device->get_vk_device(), &create_info, &swapchain_));
    return swapchain_;
  }

  // swapchain impl ---------------------------------------------------------------------------------------

  swapchain_t::swapchain_t(device device, surface surface, vk::SurfaceFormatKHR format)
      : device_(device), format_(format), vk_swapchain(create_vk_swapchain(device, surface, format))
  {
  }
}  // namespace vulkan
