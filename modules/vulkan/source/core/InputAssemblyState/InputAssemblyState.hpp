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

    void setPrimitiveTopology(PrimitiveTopology topology);

    void enablePrimitiveRestart()
    {
      vkInputAssemblyState_.primitiveRestartEnable = true;
    }

    void disablePrimitiveRestart()
    {
      vkInputAssemblyState_.primitiveRestartEnable = false;
    }

   private:
    VezInputAssemblyState vkInputAssemblyState_ = {};
  };

}  // namespace vulkan