#include "PhysicalDeviceImpl.hpp"

namespace vulkan
{
  // PhysicalDevice ---------------------------------------------------------------------------------------------------

  std::string PhysicalDevice::name() const
  {
    return pimpl_->getVkPhysicalDevice().getProperties().deviceName;
  }

  PhysicalDeviceType PhysicalDevice::type() const
  {
    switch (pimpl_->getVkPhysicalDevice().getProperties().deviceType)
    {
      case vk::PhysicalDeviceType::eOther:
        return PhysicalDeviceType::Other;
      case vk::PhysicalDeviceType::eIntegratedGpu:
        return PhysicalDeviceType::IntegratedGpu;
      case vk::PhysicalDeviceType::eDiscreteGpu:
        return PhysicalDeviceType::DiscreteGpu;
      case vk::PhysicalDeviceType::eVirtualGpu:
        return PhysicalDeviceType::VirtualGpu;
      case vk::PhysicalDeviceType::eCpu:
        return PhysicalDeviceType::Cpu;
    }
  }

}  // namespace vulkan