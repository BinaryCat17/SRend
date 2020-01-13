#include "ViewportState.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  // ViewportStateImpl ------------------------------------------------------------------------------------------------

  void ViewportStateImpl::addViewport(utils::Viewport const& viewport, utils::Rect2D const& scissor)
  {
    viewports_.push_back(toVkViewport(viewport));
    scissors_.push_back(toVkRect2D(scissor));
  }

  void ViewportStateImpl::setViewport(utils::IndexT index, utils::Viewport const& viewport)
  {
    viewports_[index] = toVkViewport(viewport);
  }

  void ViewportStateImpl::setScissor(utils::IndexT index, utils::Rect2D const& scissor)
  {
    scissors_[index] = toVkRect2D(scissor);
  }

  void ViewportStateImpl::removeViewport(utils::IndexT index)
  {
    viewports_.erase(viewports_.begin() + index);
    scissors_.erase(scissors_.begin() + index);
  }

  // ViewportState ----------------------------------------------------------------------------------------------------

  void ViewportState::addViewport(utils::Viewport const& viewport, utils::Rect2D const& scissor)
  {
    pimpl_->addViewport(viewport, scissor);
  }

  void ViewportState::setViewport(utils::IndexT index, utils::Viewport const& viewport)
  {
    pimpl_->setViewport(index, viewport);
  }

  void ViewportState::setScissor(utils::IndexT index, utils::Rect2D const& scissor)
  {
    pimpl_->setScissor(index, scissor);
  }

  void ViewportState::removeViewport(utils::IndexT index)
  {
    pimpl_->removeViewport(index);
  }

}  // namespace vulkan