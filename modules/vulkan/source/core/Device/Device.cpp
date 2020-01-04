#include "DeviceImpl.hpp"

namespace vulkan
{
  // Device -----------------------------------------------------------------------------------------------------------

  Device::Device(
      Application const& application, DeviceCreateFlags const& createFlags, PhysicalDevice const& physicalDevice)
      : pimpl_(std::make_shared<DeviceImpl>(application, createFlags, physicalDevice))
  {
  }

}  // namespace vulkan
