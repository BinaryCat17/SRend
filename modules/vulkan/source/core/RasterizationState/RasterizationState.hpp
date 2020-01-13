#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // RasterizationStateImpl -------------------------------------------------------------------------------------------

  class RasterizationStateImpl
  {
   public:
    explicit RasterizationStateImpl(std::shared_ptr<DeviceImpl> const&, RasterizationStateCreateFlags const&)
    {
    }

    RasterizationStateImpl(RasterizationStateImpl const&) = delete;

    RasterizationStateImpl(RasterizationStateImpl&&) = delete;

    RasterizationStateImpl& operator=(RasterizationStateImpl const&) = delete;

    RasterizationStateImpl& operator=(RasterizationStateImpl&&) = delete;

    [[nodiscard]] VezRasterizationState const& getVkRasterizationState() const
    {
      return rasterizationState_;
    }

    void enableDepthClamp()
    {
      rasterizationState_.depthClampEnable = true;
    }

    void disableDepthClamp()
    {
      rasterizationState_.depthClampEnable = false;
    }

    void enableRasterizerDiscard()
    {
      rasterizationState_.rasterizerDiscardEnable = true;
    }

    void disableRasterizerDiscard()
    {
      rasterizationState_.rasterizerDiscardEnable = false;
    }

    void enableDepthBias()
    {
      rasterizationState_.depthBiasEnable = true;
    }

    void disableDepthBias()
    {
      rasterizationState_.depthBiasEnable = false;
    }

    void setPolygonMode(PolygonMode mode);

    void setCullMode(CullModeFlags const& cullMode);

    void setFrontFace(FrontFace frontFace);

   private:
    VezRasterizationState rasterizationState_ = {};
  };

}  // namespace vulkan