#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // DepthStencilStateImpl --------------------------------------------------------------------------------------------

  class DepthStencilStateImpl
  {
   public:
    explicit DepthStencilStateImpl(std::shared_ptr<DeviceImpl> const&, DepthStencilStateCreateFlags const&)
    {
    }

    DepthStencilStateImpl(DepthStencilStateImpl const&) = delete;

    DepthStencilStateImpl(DepthStencilStateImpl&&) = delete;

    DepthStencilStateImpl& operator=(DepthStencilStateImpl const&) = delete;

    DepthStencilStateImpl& operator=(DepthStencilStateImpl&&) = delete;

    [[nodiscard]] VezPipelineDepthStencilState const& getVkDepthStencilState() const
    {
      return vkDepthStencilState_;
    }

    void setDepthTest(bool val) noexcept
    {
      vkDepthStencilState_.depthTestEnable = val;
    }

    void setDepthWrite(bool val) noexcept
    {
      vkDepthStencilState_.depthWriteEnable = val;
    }

    void setDepthCompareOp(CompareOp op)
    {
      vkDepthStencilState_.depthCompareOp = static_cast<VkCompareOp>(toVkCompareOp(op));
    }

    void setDepthBoundsTest(bool val) noexcept
    {
      vkDepthStencilState_.depthBoundsTestEnable = val;
    }

    void setBackStencilOp(StencilOpInfo const& state);

    void setFrontStencilOp(StencilOpInfo const& state);

    [[nodiscard]] bool getDepthTest() const noexcept
    {
      return vkDepthStencilState_.depthTestEnable;
    }

    [[nodiscard]] bool getDepthWrite() const noexcept
    {
      return vkDepthStencilState_.depthWriteEnable;
    }

    [[nodiscard]] CompareOp getDepthCompareOp() const noexcept
    {
      return static_cast<CompareOp>(vkDepthStencilState_.depthCompareOp);
    }

    [[nodiscard]] bool getDepthBoundsTest() const noexcept
    {
      return vkDepthStencilState_.depthBoundsTestEnable;
    }

    [[nodiscard]] StencilOpInfo getBackStencilOp() const noexcept
    {
      return StencilOpInfo{static_cast<StencilOp>(vkDepthStencilState_.back.failOp),
          static_cast<StencilOp>(vkDepthStencilState_.back.passOp),
          static_cast<StencilOp>(vkDepthStencilState_.back.depthFailOp),
          static_cast<CompareOp>(vkDepthStencilState_.back.compareOp)};
    }

    [[nodiscard]] StencilOpInfo getFrontStencilOp() const noexcept
    {
      return StencilOpInfo{static_cast<StencilOp>(vkDepthStencilState_.back.failOp),
          static_cast<StencilOp>(vkDepthStencilState_.back.passOp),
          static_cast<StencilOp>(vkDepthStencilState_.back.depthFailOp),
          static_cast<CompareOp>(vkDepthStencilState_.back.compareOp)};
    }

   private:
    VezPipelineDepthStencilState vkDepthStencilState_ = {};
  };

}  // namespace vulkan