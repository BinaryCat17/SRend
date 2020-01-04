#pragma once
#include "../../core/Image/Image.hpp"
#include "../surface/surface.hpp"

namespace vulkan
{
  class swapchain_t;
  using swapchain = std::shared_ptr<swapchain_t>;

  namespace device_extensions
  {
    struct swapchain : base_t
    {
      static base make()
      {
        return std::make_shared<swapchain>();
      }

      std::vector<char const*> vk_extensions() const
      {
        return {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
      }
    };
  }  // namespace device_extensions

  // swapchain ------------------------------------------------------------------------------------

  swapchain create_swapchain(device device, surface surface, vk::SurfaceFormatKHR format);

  vk::SurfaceFormatKHR get_format(swapchain swapchain);

  vk::Semaphore present(swapchain swapchain, queue queue, image image, std::vector<wait_info> const& wait_infos = {});
}  // namespace vulkan