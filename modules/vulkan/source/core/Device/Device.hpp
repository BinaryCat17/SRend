#pragma once
#include "../Application/Application.hpp"
#include "BufferManager.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  struct DeviceQueues
  {
    vk::Queue graphicQueue;
    vk::Queue computeQueue;
    vk::Queue transferQueue;
  };

  struct DeviceBuffers
  {
    BufferManager deviceLocalManager;
    BufferManager hostLocalManager;
    BufferManager hostToDeviceManager;
    BufferManager deviceToHostManager;
    BufferManager stagingManager;
  };

  // DeviceImpl -------------------------------------------------------------------------------------------------------

  class DeviceImpl
  {
   public:
    explicit DeviceImpl(std::shared_ptr<ApplicationImpl> const& application, DeviceCreateFlags const& createFlags,
        PhysicalDevice const& physicalDevice);

    DeviceImpl(DeviceImpl const&) = delete;

    DeviceImpl(DeviceImpl&&) = delete;

    DeviceImpl& operator=(DeviceImpl const&) = delete;

    DeviceImpl& operator=(DeviceImpl&&) = delete;

    [[nodiscard]] std::shared_ptr<ApplicationImpl> const& getApplication() const
    {
      return application_;
    }

    [[nodiscard]] std::shared_ptr<PhysicalDeviceImpl> const& getPhysicalDevice() const
    {
      return physicalDevice_;
    }

    [[nodiscard]] vk::Device getVkDevice() const
    {
      return vkDevice_.get();
    }

    [[nodiscard]] DeviceQueues& getQueues()
    {
      return queues_;
    }

    [[nodiscard]] DeviceBuffers& getBuffers()
    {
      return buffers_;
    }

   private:
    std::shared_ptr<ApplicationImpl> application_;
    std::shared_ptr<PhysicalDeviceImpl> physicalDevice_;
    std::unique_ptr<VkDevice_T, decltype(vezDestroyDevice)*> vkDevice_;
    DeviceQueues queues_;
    DeviceBuffers buffers_;
  };

}  // namespace vulkan