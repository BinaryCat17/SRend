#include "ViewportState.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  vk::Rect2D toVkScissor(Viewport const& viewport)
  {
    return {{static_cast<int32_t>(viewport.getPosition().x()), static_cast<int32_t>(viewport.getPosition().y())},
        {static_cast<uint32_t>(viewport.getExtent().width()), static_cast<uint32_t>(viewport.getExtent().height())}};
  }

  // Viewport ---------------------------------------------------------------------------------------------------------

  Viewport::Viewport(Device const& device, ViewportCreateFlags const& createFlags)
      : pimpl_(std::make_shared<ViewportImpl>(device.getImpl(), createFlags))
  {
  }

  void Viewport::setExtent(utils::Extent2Df const& val) noexcept
  {
    pimpl_->setExtent(val);
  }

  void Viewport::setPosition(utils::Position2Df const& val) noexcept
  {
    pimpl_->setPosition(val);
  }

  void Viewport::setMinDepth(float val) noexcept
  {
    pimpl_->setMinDepth(val);
  }

  void Viewport::setMaxDepth(float val) noexcept
  {
    pimpl_->setMaxDepth(val);
  }

  void Viewport::setViewport(utils::Viewport const& val) noexcept
  {
    return pimpl_->setViewport(val);
  }

  utils::Extent2Df Viewport::getExtent() const noexcept
  {
    return pimpl_->getExtent();
  }

  utils::Position2Df Viewport::getPosition() const noexcept
  {
    return pimpl_->getPosition();
  }

  float Viewport::getMinDepth() const noexcept
  {
    return pimpl_->getMinDepth();
  }

  float Viewport::getMaxDepth() const noexcept
  {
    return pimpl_->getMaxDepth();
  }

  utils::Viewport Viewport::getViewport() const noexcept
  {
    return pimpl_->getViewport();
  }

  // ViewportStateImpl ------------------------------------------------------------------------------------------------

  void ViewportStateImpl::addViewport(Viewport const& viewport)
  {
    viewports_.insert({viewport, toVkScissor(viewport)});
    needUpdate_ = true;
  }

  void ViewportStateImpl::removeViewport(Viewport const& viewport)
  {
    viewports_.erase(viewport);
    needUpdate_ = true;
  }

  void ViewportStateImpl::setScissor(Viewport const& viewport, utils::Rect2D const& scissor) noexcept
  {
    viewports_.at(viewport) = toVkRect2D(scissor);
    needUpdate_ = true;
  }

  utils::Rect2D ViewportStateImpl::getScissor(Viewport const& viewport) noexcept
  {
    auto vkScissor = viewports_.at(viewport);

    return utils::Rect2D(vkScissor.offset.x, vkScissor.offset.y, vkScissor.extent.width, vkScissor.extent.height);
  }

  void ViewportStateImpl::update()
  {
    if (needUpdate_)
    {
      needUpdate_ = false;

      vkViewports_.clear();
      vkScissors_.clear();

      for (auto const& p : viewports_)
      {
        vkViewports_.push_back(toVkViewport(p.first.getViewport()));
        vkScissors_.push_back(p.second);
      }
    }
  }

  // ViewportState ----------------------------------------------------------------------------------------------------

  ViewportState::ViewportState(Device const& device, ViewportStateCreateFlags const& createFlags)
      : pimpl_(std::make_shared<ViewportStateImpl>(device.getImpl(), createFlags))
  {
  }

  void ViewportState::addViewport(Viewport const& viewport)
  {
    pimpl_->addViewport(viewport);
  }

  void ViewportState::removeViewport(Viewport const& viewport)
  {
    pimpl_->removeViewport(viewport);
  }

  void ViewportState::setScissor(Viewport const& viewport, utils::Rect2D const& scissor) noexcept
  {
    pimpl_->setScissor(viewport, scissor);
  }

  [[nodiscard]] utils::Rect2D ViewportState::getScissor(Viewport const& viewport) noexcept
  {
    return pimpl_->getScissor(viewport);
  }

}  // namespace vulkan