#pragma once
#include <utils/signals.hpp>
#include "BaseWindow.hpp"

namespace wsystem
{
  // WindowImpl -------------------------------------------------------------------------------------------------------

  class BaseManager;

  class WindowImpl
  {
   public:
    WindowImpl(std::shared_ptr<BaseWindow> pbase, std::shared_ptr<BaseManager> pmanager)
        : pbase_(std::move(pbase)), pmanager_(std::move(pmanager))
    {
    }

    ~WindowImpl();

    [[nodiscard]] std::shared_ptr<BaseWindow> getBase() const
    {
      return pbase_;
    }

    void setSize(utils::Extent2D const& newSize)
    {
      pbase_->setSize(newSize);
    }

    [[nodiscard]] utils::Extent2D getSize() const
    {
      return pbase_->getSize();
    }

    void setPosition(utils::Position2D const& newPosition)
    {
      pbase_->setPosition(newPosition);
    }

    [[nodiscard]] utils::Position2D getPosition() const
    {
      return pbase_->getPosition();
    }

    void setTitle(std::string const& newTitle)
    {
      pbase_->setTitle(newTitle);
    }

    [[nodiscard]] std::string getTitle() const
    {
      return pbase_->getTitle();
    }

    void applyOptions(WindowOptionsFlags options)
    {
      pbase_->applyOptions(options);
    }

    void offOptions(WindowOptionsFlags options)
    {
      pbase_->offOptions(options);
    }

    // signals

    void update();

    Window::Signal onShouldClose;

    Window::Signal onResize;

    Window::Signal onMove;

   private:
    std::shared_ptr<BaseWindow> pbase_;
    std::shared_ptr<BaseManager> pmanager_;
  };

}  // namespace wsystem