#pragma once
#include <utils/signals.hpp>
#include <utils/utils.hpp>

namespace wsystem
{
  // utils ------------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(WindowCreate, {
    vulkan = 1u << 0u,
    opengl = 1u << 1u
  };)

  SR_MAKE_BIT_FLAGS(WindowOptions, {
    resizable = 1u << 0u,
    hidden = 1u << 1u,
    fullscreen = 1u << 2u,
    maximized = 1u << 3u,
    minimazed = 1u << 4u,
    borderless = 1u << 5u
  };)

  // clang-format on

  // Window -----------------------------------------------------------------------------------------------------------

  class WindowImpl;

  class Window
  {
   public:
    explicit Window(std::shared_ptr<WindowImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<WindowImpl> getImpl() const
    {
      return pimpl_;
    }

    // parameters

    void setSize(utils::Extent2D const& newSize);

    [[nodiscard]] utils::Extent2D getSize() const;

    void setPosition(utils::Position2D const& newPosition);

    [[nodiscard]] utils::Position2D getPosition() const;

    void setTitle(std::string const& newTitle);

    [[nodiscard]] std::string getTitle() const;

    void applyOptions(WindowOptionsFlags options);

    void offOptions(WindowOptionsFlags options);

    // signals

    using Signal = utils::signals::Signal<void()>;

    Signal& onShouldClose();

    Signal& onResize();

    Signal& onMove();

   private:
    std::shared_ptr<WindowImpl> pimpl_;
  };

}  // namespace wsystem
