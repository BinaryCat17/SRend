#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
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
      return viewports_;
    }

    [[nodiscard]] std::vector<vk::Viewport> const& getVkScissors() const
    {
      return viewports_;
    }

    void addViewport(utils::Viewport const& viewport, utils::Rect2D const& scissor);

    void setViewport(utils::IndexT index, utils::Viewport const& viewport);

    void setScissor(utils::IndexT index, utils::Rect2D const& scissor);

    void removeViewport(utils::IndexT index);

   private:
    std::vector<vk::Viewport> viewports_;
    std::vector<vk::Rect2D> scissors_;
  };

}  // namespace vulkan