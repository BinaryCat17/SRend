#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // InputAssemblyStateImpl -------------------------------------------------------------------------------------------

  class InputAssemblyStateImpl
  {
   public:
    explicit InputAssemblyStateImpl(std::shared_ptr<DeviceImpl> const&, InputAssemblyStateCreateFlags const&)
    {
    }

    InputAssemblyStateImpl(InputAssemblyStateImpl const&) = delete;

    InputAssemblyStateImpl(InputAssemblyStateImpl&&) = delete;

    InputAssemblyStateImpl& operator=(InputAssemblyStateImpl const&) = delete;

    InputAssemblyStateImpl& operator=(InputAssemblyStateImpl&&) = delete;

    [[nodiscard]] VezInputAssemblyState const& getVkInputAssemblyState() const
    {
      return vkInputAssemblyState_;
    }

    void setPrimitiveRestart(bool val) noexcept
    {
      vkInputAssemblyState_.primitiveRestartEnable = val;
    }

    [[nodiscard]] bool getPrimitiveRestart() const noexcept
    {
      return vkInputAssemblyState_.primitiveRestartEnable;
    }

    void setPrimitiveTopology(PrimitiveTopology topology)
    {
      vkInputAssemblyState_.topology = static_cast<VkPrimitiveTopology>(topology);
    }

    [[nodiscard]] PrimitiveTopology getPrimitiveTopology() const noexcept
    {
      return static_cast<PrimitiveTopology>(vkInputAssemblyState_.topology);
    }
   private:
    VezInputAssemblyState vkInputAssemblyState_ = {};
  };

}  // namespace vulkan