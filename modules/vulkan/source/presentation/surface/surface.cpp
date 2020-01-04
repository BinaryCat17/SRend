#include "../../core/Queue/QueueImpl.hpp"
#include "../../core/physical_device/PhysicalDeviceImpl.hpp"
#include "surface_t.hpp"

namespace vulkan
{
  // surface
  // ----------------------------------------------------------------------------------------------

  surface create_surface(application application, wsystem::Window window)
  {
    return std::make_shared<surface_t>(application, window);
  }

  vk::SurfaceCapabilitiesKHR get_capabilities(surface surface, physical_device physical_device)
  {
    return physical_device->get_vk_physical_device().getSurfaceCapabilitiesKHR(surface->get_vk_surface());
  }

  bool get_support(surface surface, queue queue)
  {
    return queue->get_physical_device()->get_vk_physical_device().getSurfaceSupportKHR(
        queue->get_family_index(), surface->get_vk_surface());
  }
}  // namespace vulkan