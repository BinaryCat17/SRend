#include "vulkan.hpp"
#include "../Manager/BaseManager.hpp"
#include "../Window/WindowImpl.hpp"

namespace wsystem
{
  std::vector<char const*> getVulkanInstanceExtensions(const Manager& manager)
  {
    return manager.getBase()->getInstanceExtensions();
  }

  VkSurfaceKHR createVulkanSurface(const Window& window, VkInstance instance)
  {
    return window.getImpl()->getBase()->createSurface(instance);
  }

}  // namespace wsystem
