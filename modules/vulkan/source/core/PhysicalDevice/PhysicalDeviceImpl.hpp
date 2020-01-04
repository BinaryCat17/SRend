#pragma once
#include "../../utils.hpp"
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

    [[nodiscard]] vk::PhysicalDevice getVkPhysicalDevice() const
    {
      return vkPhysicalDevice_;
    }

   private:
    vk::PhysicalDevice vkPhysicalDevice_;
  };

}  // namespace vulkan