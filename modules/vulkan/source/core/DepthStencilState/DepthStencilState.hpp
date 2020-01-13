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

    void enableDepthTest()
    {
      vkDepthStencilState_.depthTestEnable = true;
    }

    void disableDepthTest()
    {
      vkDepthStencilState_.depthTestEnable = false;
    }

    void enableDepthWrite()
    {
      vkDepthStencilState_.depthWriteEnable = true;
    }

    void disableDepthWrite()
    {
      vkDepthStencilState_.depthWriteEnable = false;
    }

    void setDepthCompareOp(CompareOp op)
    {
      vkDepthStencilState_.depthCompareOp = static_cast<VkCompareOp>(toVkCompareOp(op));
    }

    void enableDepthBoundsTest()
    {
      vkDepthStencilState_.depthBoundsTestEnable = true;
    }

    void disableDepthBoundsTest()
    {
      vkDepthStencilState_.depthBoundsTestEnable = false;
    }

    void setBackStencilOp(StencilOpInfo const& state);

    void setFrontStencilOp(StencilOpInfo const& state);

   private:
    VezPipelineDepthStencilState vkDepthStencilState_ = {};
  };

}  // namespace vulkan