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

  VezMemoryFlags toVkMemoryFlags(MemoryType type);

  // DeviceImpl -------------------------------------------------------------------------------------------------------

  class DeviceImpl
  {
   public:
    explicit DeviceImpl(std::shared_ptr<ApplicationImpl> const& application, DeviceCreateFlags const& createFlags,
        PhysicalDevice const& physicalDevice);

    ~DeviceImpl();

    DeviceImpl(DeviceImpl const&) = delete;

    DeviceImpl(DeviceImpl&&) = delete;

    DeviceImpl& operator=(DeviceImpl const&) = delete;

    DeviceImpl& operator=(DeviceImpl&&) = delete;

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

    // interface

   private:
    std::shared_ptr<ApplicationImpl> application_;
    vk::Device vkDevice_;
    DeviceQueues queues_;
    DeviceBuffers buffers_;
  };

}  // namespace vulkan