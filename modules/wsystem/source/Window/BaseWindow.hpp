#pragma once
#include "Window.hpp"

namespace wsystem
{
  // BaseWindow -------------------------------------------------------------------------------------------------------

  class BaseWindow
  {
   public:
    virtual ~BaseWindow() = default;

    // parameters

    virtual void setSize(utils::Extent2D const& newSize) = 0;

    [[nodiscard]] virtual utils::Extent2D getSize() const = 0;

    virtual void setPosition(utils::Position2D const& newPosition) = 0;

    [[nodiscard]] virtual utils::Position2D getPosition() const = 0;

    virtual void setTitle(std::string const& newTitle) = 0;

    [[nodiscard]] virtual std::string getTitle() const = 0;

    virtual void applyOptions(WindowOptionsFlags options) = 0;

    virtual void offOptions(WindowOptionsFlags options) = 0;

    // signals

    [[nodiscard]] virtual bool isShouldClose() const = 0;

    [[nodiscard]] virtual bool isResized() const = 0;

    [[nodiscard]] virtual bool isMoved() const = 0;
  };
}  // namespace wsystem