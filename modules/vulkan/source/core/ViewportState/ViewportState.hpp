#pragma once
#include "../Device/Device.hpp"
#include <map>

namespace vulkan
{
  // ViewportImpl -----------------------------------------------------------------------------------------------------

  class ViewportImpl
  {
   public:
    explicit ViewportImpl(std::shared_ptr<DeviceImpl> const&, ViewportCreateFlags const&)
    {
    }

    void setExtent(utils::Extent2Df const& val) noexcept
    {
      viewport_.setWidth(val.width());
      viewport_.setHeight(val.height());
    }

    void setPosition(utils::Position2Df const& val) noexcept
    {
      viewport_.setX(val.x());
      viewport_.setY(val.y());
    }

    void setMinDepth(float val) noexcept
    {
      viewport_.setMinDepth(val);
    }

    void setMaxDepth(float val) noexcept
    {
      viewport_.setMaxDepth(val);
    }

    void setViewport(utils::Viewport const& val) noexcept
    {
      viewport_ = val;
    }

    [[nodiscard]] utils::Extent2Df getExtent() const noexcept
    {
      return utils::Extent2Df(viewport_.width(), viewport_.height());
    }

    [[nodiscard]] utils::Position2Df getPosition() const noexcept
    {
      return utils::Position2Df (viewport_.x(), viewport_.y());
    }

    [[nodiscard]] float getMinDepth() const noexcept
    {
      return viewport_.minDepth();
    }

    [[nodiscard]] float getMaxDepth() const noexcept
    {
      return viewport_.maxDepth();
    }

    [[nodiscard]] utils::Viewport getViewport() const noexcept
    {
      return viewport_;
    }

   private:
    utils::Viewport viewport_;
  };

  // ViewportStateImpl ------------------------------------------------------------------------------------------------

  class ViewportStateImpl
  {
   public:
    explicit ViewportStateImpl(std::shared_ptr<DeviceImpl> const&, ViewportStateCreateFlags const&)
    {
    }

    ViewportStateImpl(ViewportStateImpl const&) = delete;

    ViewportStateImpl(ViewportStateImpl&&) = delete;

    ViewportStateImpl& operator=(ViewportStateImpl const&) = delete;

    ViewportStateImpl& operator=(ViewportStateImpl&&) = delete;

    [[nodiscard]] std::vector<vk::Viewport> const& getVkViewports() const
    {
      return vkViewports_;
    }

    [[nodiscard]] std::vector<vk::Rect2D> const& getVkScissors() const
    {
      return vkScissors_;
    }

    void addViewport(Viewport const& viewport);

    void removeViewport(Viewport const& viewport);

    void setScissor(Viewport const& viewport, utils::Rect2D const& scissor) noexcept;

    [[nodiscard]] utils::Rect2D getScissor(Viewport const& viewport) noexcept;

    void update();

   private:
    std::map<Viewport, vk::Rect2D> viewports_;
    bool needUpdate_ = true;
    std::vector<vk::Viewport> vkViewports_;
    std::vector<vk::Rect2D> vkScissors_;
  };

}  // namespace vulkan