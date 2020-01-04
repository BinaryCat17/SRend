#include "BufferImpl.hpp"

namespace vulkan
{
  // DeviceLocalBuffer ------------------------------------------------------------------------------------------------

  std::shared_ptr<DeviceLocalBuffer> createDeviceLocalBuffer(
      Device const& device, BufferCreateFlags const&, utils::SizeT size, utils::AlignmentT alignment)
  {
    auto alloc = device.getImpl()->getBuffers().deviceLocalManager.allocate(size, alignment);

    return std::make_shared<DeviceLocalBufferImpl>(device, alloc.first, alloc.second);
  }

  // DeviceLocalBuffer ------------------------------------------------------------------------------------------------

  std::shared_ptr<HostLocalBuffer> createHostLocalBuffer(
      Device const& device, BufferCreateFlags const&, utils::SizeT size, utils::AlignmentT alignment)
  {
    auto alloc = device.getImpl()->getBuffers().hostLocalManager.allocate(size, alignment);

    return std::make_shared<HostLocalBufferImpl>(device, alloc.first, alloc.second);
  }

  std::shared_ptr<HostLocalBuffer> createStagingBuffer(
      Device const& device, BufferCreateFlags const&, utils::SizeT size, utils::AlignmentT alignment)
  {
    auto alloc = device.getImpl()->getBuffers().stagingManager.allocate(size, alignment);

    return std::make_shared<HostLocalBufferImpl>(device, alloc.first, alloc.second);
  }

  // DeviceVisibleBuffer ----------------------------------------------------------------------------------------------

  std::shared_ptr<DeviceVisibleBuffer> createDeviceVisibleBuffer(
      Device const& device, BufferCreateFlags const&, utils::SizeT size, utils::AlignmentT alignment)
  {
    auto alloc = device.getImpl()->getBuffers().deviceVisibleManager.allocate(size, alignment);

    return std::make_shared<DeviceVisibleBufferImpl>(device, alloc.first, alloc.second);
  }

}  // namespace vulkan