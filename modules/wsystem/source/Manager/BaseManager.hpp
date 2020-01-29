#pragma once
#include "../Window/BaseWindow.hpp"
#include "Manager.hpp"



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
  };

}  // namespace wsystem