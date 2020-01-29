#include "PhysicalDevice.hpp"

namespace vulkan
{
  // PhysicalDeviceImpl -----------------------------------------------------------------------------------------------

  PhysicalDeviceType PhysicalDeviceImpl::type() const
  {
    switch (vkPhysicalDevice_.getProperties().deviceType)
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
    throw std::runtime_error("undefined device type");
  }

  // PhysicalDevice ---------------------------------------------------------------------------------------------------

  std::string PhysicalDevice::name() const noexcept
  {
    return pimpl_->name();
  }

  PhysicalDeviceType PhysicalDevice::type() const noexcept
  {
    return pimpl_->type();
  }

}  // namespace vulkan