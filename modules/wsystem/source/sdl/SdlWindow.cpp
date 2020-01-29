#include "SdlWindow.hpp"
#include "SDL_vulkan.h"

namespace wsystem
{
  // utils ----------------------------------------------------------------------------------------

  Uint32 toSdlWindowCreateFlags(WindowCreateFlags flags)
  {
    Uint32 result = 0;
    if (flags & WindowCreateFlagBits::vulkan)
    {
      result |= SDL_WINDOW_VULKAN;
    }
    if (flags & WindowCreateFlagBits::opengl)
    {
      result |= SDL_WINDOW_OPENGL;
    }
    return result;
  }

  void applySdlWindowFlags(UniqueSdlWindow const& window, WindowOptionsFlags flags)
  {
    if (flags & WindowOptionsFlagBits::borderless)
    {
      SDL_SetWindowBordered(window.get(), SDL_TRUE);
    }
    if (flags & WindowOptionsFlagBits::fullscreen)
    {
      SDL_SetWindowFullscreen(window.get(), SDL_TRUE);
    }
    if (flags & WindowOptionsFlagBits::hidden)
    {
      SDL_HideWindow(window.get());
    }
    if (flags & WindowOptionsFlagBits::maximized)
    {
      SDL_MaximizeWindow(window.get());
    }
    if (flags & WindowOptionsFlagBits::minimazed)
    {
      SDL_MinimizeWindow(window.get());
    }
    if (flags & WindowOptionsFlagBits::resizable)
    {
      SDL_SetWindowResizable(window.get(), SDL_TRUE);
    }
  }

  void offSdlWindowFlags(UniqueSdlWindow const& window, WindowOptionsFlags flags)
  {
    if (flags & WindowOptionsFlagBits::borderless)
    {
      SDL_SetWindowBordered(window.get(), SDL_FALSE);
    }
    if (flags & WindowOptionsFlagBits::fullscreen)
    {
      SDL_SetWindowFullscreen(window.get(), SDL_FALSE);
    }
    if (flags & WindowOptionsFlagBits::hidden)
    {
      SDL_ShowWindow(window.get());
    }
    if (flags & WindowOptionsFlagBits::maximized)
    {
    }
    if (flags & WindowOptionsFlagBits::minimazed)
    {
    }
    if (flags & WindowOptionsFlagBits::resizable)
    {
      SDL_SetWindowResizable(window.get(), SDL_FALSE);
    }
  }

  UniqueSdlWindow createSdlWindow(
      std::string const& title, utils::Extent2D const& extent, WindowCreateFlags createFlags)
  {
    UniqueSdlWindow window(
        SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            static_cast<int>(extent.width()), static_cast<int>(extent.height()), toSdlWindowCreateFlags(createFlags)),
        SDL_DestroyWindow);

    if (!window)
    {
      throw std::runtime_error(SDL_GetError());
    }

    return window;
  }

  // SdlWindow ------------------------------------------------------------------------------------

  SdlWindow::SdlWindow(std::string const& title, utils::Extent2D const& extent, WindowCreateFlags createFlags)
      : window_(createSdlWindow(title, extent, createFlags))
  {
  }

  void SdlWindow::setSize(utils::Extent2D const& newSize)
  {
    SDL_SetWindowSize(window_.get(), static_cast<int>(newSize.width()), static_cast<int>(newSize.height()));
  }

  utils::Extent2D SdlWindow::getSize() const
  {
    int width = 0, height = 0;
    SDL_GetWindowSize(window_.get(), &width, &height);
    return utils::Extent2D(static_cast<unsigned>(width), static_cast<unsigned>(height));
  }

  void SdlWindow::setPosition(utils::Position2D const& newPosition)
  {
    SDL_SetWindowPosition(window_.get(), static_cast<int>(newPosition.x()), static_cast<int>(newPosition.y()));
  }

  utils::Position2D SdlWindow::getPosition() const
  {
    int x = 0, y = 0;
    SDL_GetWindowPosition(window_.get(), &x, &y);
    return utils::Position2D(static_cast<unsigned>(x), static_cast<unsigned>(y));
  }

  void SdlWindow::setTitle(std::string const& newTitle)
  {
    SDL_SetWindowTitle(window_.get(), newTitle.c_str());
  }

  std::string SdlWindow::getTitle() const
  {
    return SDL_GetWindowTitle(window_.get());
  }

  void SdlWindow::applyOptions(WindowOptionsFlags options)
  {
    applySdlWindowFlags(window_, options);
  }

  void SdlWindow::offOptions(WindowOptionsFlags options)
  {
    offSdlWindowFlags(window_, options);
  }

  bool SdlWindow::isShouldClose() const
  {
    return isShouldClose_;
  }

  bool SdlWindow::isResized() const
  {
    return isResized_;
  }

  bool SdlWindow::isMoved() const
  {
    return isMoved_;
  }

  VkSurfaceKHR SdlWindow::createSurface(VkInstance instance) const
  {
    VkSurfaceKHR result;
    if (!SDL_Vulkan_CreateSurface(window_.get(), instance, &result))
    {
      throw std::runtime_error(SDL_GetError());
    }
    return result;
  }

}  // namespace wsystem