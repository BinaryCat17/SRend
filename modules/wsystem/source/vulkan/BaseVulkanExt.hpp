#pragma once
#include "../Window/BaseWindow.hpp"
#include "vulkan.hpp"

namespace wsystem
{
  // BaseVulkanExt ----------------------------------------------------------------------------------------------------

  class BaseVulkanExt
  {
   public:
    virtual ~BaseVulkanExt() = default;

    virtual std::vector<char const*> getInstanceExtensions() const = 0;

    virtual VkSurfaceKHR createSurface(std::shared_ptr<BaseWindow> const& window, VkInstance instance) const = 0;
  };

}  // namespace wsystem