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

    void setDepthClamp(bool val) noexcept
    {
      rasterizationState_.depthClampEnable = val;
    }

    void setRasterizerDiscard(bool val) noexcept
    {
      rasterizationState_.rasterizerDiscardEnable = val;
    }

    void setDepthBias(bool val) noexcept
    {
      rasterizationState_.depthBiasEnable = val;
    }

    void setPolygonMode(PolygonMode mode)
    {
      rasterizationState_.polygonMode = toVkPolygonMode(mode);
    }

    void setCullMode(CullModeFlags const& cullMode)
    {
      rasterizationState_.cullMode = toVkCullModeFlags(cullMode);
    }

    void setFrontFace(FrontFace frontFace)
    {
      rasterizationState_.frontFace = toVkFrontFace(frontFace);
    }

    [[nodiscard]] bool getDepthClamp() const noexcept
    {
      return rasterizationState_.depthClampEnable;
    }

    [[nodiscard]] bool getRasterizerDiscard() const noexcept
    {
      return rasterizationState_.rasterizerDiscardEnable;
    }

    [[nodiscard]] bool getDepthBias() const noexcept
    {
      return rasterizationState_.depthBiasEnable;
    }

    [[nodiscard]] PolygonMode getPolygonMode() const noexcept
    {
      return static_cast<PolygonMode>(rasterizationState_.polygonMode);
    }

    [[nodiscard]] CullModeFlags getCullMode() const noexcept
    {
      return static_cast<CullModeFlags>(rasterizationState_.cullMode);
    }

    [[nodiscard]] FrontFace getFrontFace() const noexcept
    {
      return static_cast<FrontFace>(rasterizationState_.frontFace);
    }

   private:
    VezRasterizationState rasterizationState_ = {};
  };

}  // namespace vulkan