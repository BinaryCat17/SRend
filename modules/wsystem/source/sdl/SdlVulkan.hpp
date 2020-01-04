#pragma once
#include "../vulkan/BaseVulkanExt.hpp"

namespace wsystem
{
  class SdlVulkan : public BaseVulkanExt
  {
   public:
    [[nodiscard]] std::vector<char const*> getInstanceExtensions() const override;

    VkSurfaceKHR createSurface(std::shared_ptr<BaseWindow> const& window, VkInstance instance) const override;
  };

}  // namespace wsystem