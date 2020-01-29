#pragma once
#include <SDL.h>
#include "../Window/WindowImpl.hpp"

namespace wsystem
{
  // SdlWindow ------------------------------------------------------------------------------------

  using UniqueSdlWindow = std::unique_ptr<SDL_Window, decltype(SDL_DestroyWindow)*>;

  class SdlWindow : public BaseWindow
  {
   public:
    SdlWindow(std::string const& title, utils::Extent2D const& extent, WindowCreateFlags createFlags);

    [[nodiscard]] UniqueSdlWindow const& getSdlWindow() const
    {
      return window_;
    }

    [[nodiscard]] NativeHandle getNativeHandle() const override
    {
      return window_.get();
    }

    // parameters

    void setSize(utils::Extent2D const& newSize) override;

    [[nodiscard]] utils::Extent2D getSize() const override;

    void setPosition(utils::Position2D const& newPosition) override;

    [[nodiscard]] utils::Position2D getPosition() const override;

    void setTitle(std::string const& newTitle) override;

    [[nodiscard]] std::string getTitle() const override;

    void applyOptions(WindowOptionsFlags options) override;

    void offOptions(WindowOptionsFlags options) override;

    // signals

    [[nodiscard]] bool isShouldClose() const override;

    [[nodiscard]] bool isResized() const override;

    [[nodiscard]] bool isMoved() const override;

    void setIsShouldClose(bool value)
    {
      isShouldClose_ = value;
    }

    void setIsResized(bool value)
    {
      isResized_ = value;
    }

    void setIsMoved(bool value)
    {
      isMoved_ = value;
    }

    // vulkan

    VkSurfaceKHR createSurface(VkInstance instance) const override;

   private:
    UniqueSdlWindow window_;
    bool isShouldClose_ = false;
    bool isResized_ = false;
    bool isMoved_ = false;
  };

}  // namespace wsystem