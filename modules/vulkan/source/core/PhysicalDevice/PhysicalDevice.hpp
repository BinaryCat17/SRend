#pragma once
#include "../Application/Application.hpp"
#include "PhysicalDevice.hpp"

namespace vulkan
{
  // PhysicalDeviceImpl -----------------------------------------------------------------------------------------------

  class PhysicalDeviceImpl
  {
   public:
    explicit PhysicalDeviceImpl(vk::PhysicalDevice vkPhysicalDevice) : vkPhysicalDevice_(vkPhysicalDevice)
    {
    }

    PhysicalDeviceImpl(PhysicalDeviceImpl const&) = delete;

    PhysicalDeviceImpl(PhysicalDeviceImpl&&) = delete;

    PhysicalDeviceImpl& operator=(PhysicalDeviceImpl const&) = delete;

    PhysicalDeviceImpl& operator=(PhysicalDeviceImpl&&) = delete;

    [[nodiscard]] vk::PhysicalDevice getVkPhysicalDevice() const
    {
      return vkPhysicalDevice_;
    }

    [[nodiscard]] std::string name() const
    {
      return vkPhysicalDevice_.getProperties().deviceName;
    }

    [[nodiscard]] PhysicalDeviceType type() const;

   private:
    vk::PhysicalDevice vkPhysicalDevice_;
  };

}  // namespace vulkan