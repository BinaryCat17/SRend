#include "WindowImpl.hpp"

namespace wsystem
{
  // Window -----------------------------------------------------------------------------------------------------------

  void Window::setSize(utils::Extent2D const& newSize)
  {
    pimpl_->setSize(newSize);
  }

  utils::Extent2D Window::getSize() const
  {
    return pimpl_->getSize();
  }

  void Window::setPosition(utils::Position2D const& newPosition)
  {
    pimpl_->setPosition(newPosition);
  }

  utils::Position2D Window::getPosition() const
  {
    return pimpl_->getPosition();
  }

  void Window::setTitle(std::string const& newTitle)
  {
    pimpl_->setTitle(newTitle);
  }

  std::string Window::getTitle() const
  {
    return pimpl_->getTitle();
  }

  void Window::applyOptions(WindowOptionsFlags options)
  {
    pimpl_->applyOptions(options);
  }

  void Window::offOptions(WindowOptionsFlags options)
  {
    pimpl_->offOptions(options);
  }

  Window::Signal& Window::onShouldClose()
  {
    return pimpl_->onShouldClose;
  }

  Window::Signal& Window::onResize()
  {
    return pimpl_->onResize;
  }

  Window::Signal& Window::onMove()
  {
    return pimpl_->onMove;
  }

}  // namespace wsystem
