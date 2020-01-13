#pragma once
#include "../Window/BaseWindow.hpp"
#include "Manager.hpp"

struct VkSurfaceKHR_T;
typedef VkSurfaceKHR_T* VkSurfaceKHR;

struct VkInstance_T;
typedef VkInstance_T* VkInstance;

namespace wsystem
{
  // BaseManager ------------------------------------------------------------------------------------------------------

  class BaseManager
  {
   public:
    virtual ~BaseManager() = default;

    virtual std::shared_ptr<BaseWindow> createWindow(
        std::string const& title, utils::Extent2D const& extent, WindowCreateFlags createFlags) = 0;

    virtual void removeWindow(std::shared_ptr<BaseWindow> window) = 0;

    virtual void update() = 0;

    virtual std::vector<char const*> getInstanceExtensions() const = 0;

    [[nodiscard]] virtual VkSurfaceKHR createSurface(
        std::shared_ptr<BaseWindow> const& window, VkInstance instance) const = 0;
  };

}  // namespace wsystem