#pragma once
#include "../Manager/Manager.hpp"

struct VkSurfaceKHR_T;
typedef VkSurfaceKHR_T* VkSurfaceKHR;
struct VkInstance_T;
typedef VkInstance_T* VkInstance;

namespace wsystem
{
  std::vector<char const*> getVulkanInstanceExtensions(const Manager& manager);

  VkSurfaceKHR createVulkanSurface(const Manager& manager, const Window& window, VkInstance instance);

}  // namespace wsystem