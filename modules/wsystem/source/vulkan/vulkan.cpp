#include "vulkan.hpp"
#include "../Manager/BaseManager.hpp"
#include "../Window/WindowImpl.hpp"

namespace wsystem
{
  std::vector<char const*> getVulkanInstanceExtensions(const Manager& manager)
  {
    return manager.getBase()->getInstanceExtensions();
  }

  VkSurfaceKHR createVulkanSurface(const Manager& manager, const Window& window, VkInstance instance)
  {
    return manager.getBase()->createSurface(window.getImpl()->getBase(), instance);
  }

}  // namespace wsystem
