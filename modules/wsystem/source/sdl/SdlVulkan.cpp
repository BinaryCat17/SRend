#include "SdlVulkan.hpp"
#include "SDL_vulkan.h"
#include "SdlWindow.hpp"

namespace wsystem
{
  std::vector<char const *> SdlVulkan::getInstanceExtensions() const
  {
    unsigned count = 0;
    if (!SDL_Vulkan_GetInstanceExtensions(nullptr, &count, nullptr))
    {
      throw std::runtime_error(SDL_GetError());
    }
    std::vector<char const *> extensions(count);
    if (!SDL_Vulkan_GetInstanceExtensions(nullptr, &count, extensions.data()))
    {
      throw std::runtime_error(SDL_GetError());
    }
    return extensions;
  }

  VkSurfaceKHR SdlVulkan::createSurface(std::shared_ptr<BaseWindow> const &window, VkInstance instance) const
  {
    VkSurfaceKHR result;
    if (!SDL_Vulkan_CreateSurface(
            std::dynamic_pointer_cast<SdlWindow>(window)->getSdlWindow().get(), instance, &result))
    {
      throw std::runtime_error(SDL_GetError());
    }
    return result;
  }

}  // namespace wsystem
