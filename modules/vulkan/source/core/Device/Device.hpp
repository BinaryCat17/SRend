#pragma once
#include "../Application/Application.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(DeviceCreate, {};)

  // clang-format on

  // Device -----------------------------------------------------------------------------------------------------------

  class DeviceImpl;

  class Device
  {
   public:
    explicit Device(std::shared_ptr<DeviceImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<DeviceImpl> const& getImpl() const
    {
      return pimpl_;
    }

    explicit Device(
        Application const& application, DeviceCreateFlags const& createFlags, PhysicalDevice const& physicalDevice);

   private:
    std::shared_ptr<DeviceImpl> pimpl_;
  };

}  // namespace vulkan