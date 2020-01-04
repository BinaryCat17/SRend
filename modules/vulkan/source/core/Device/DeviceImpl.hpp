#pragma once
#include "../Application/ApplicationImpl.hpp"
#include "BufferManager.hpp"
#include "Device.hpp"

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
    BufferManager deviceVisibleManager;
    BufferManager stagingManager;
  };

  // DeviceImpl -------------------------------------------------------------------------------------------------------

  class DeviceImpl
  {
   public:
    explicit DeviceImpl(
        Application const& application, DeviceCreateFlags const& createFlags, PhysicalDevice const& physicalDevice);

    ~DeviceImpl();

    [[nodiscard]] vk::Device getVkDevice() const
    {
      return vkDevice_;
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
    Application application_;
    vk::Device vkDevice_;
    DeviceQueues queues_;
    DeviceBuffers buffers_;
  };

}  // namespace vulkan