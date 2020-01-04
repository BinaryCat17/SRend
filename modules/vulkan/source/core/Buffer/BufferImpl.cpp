#include "BufferImpl.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  void memCopyToBuffer(
      vk::Device device, vk::Buffer buffer, void const* pData, utils::SizeT size, utils::OffsetT offset)
  {
    void* pMappedData = nullptr;
    vezMapBuffer(device, buffer, offset, size, &pMappedData);
    memcpy(reinterpret_cast<char*>(pMappedData) + offset, pData, size);
    vezUnmapBuffer(device, buffer);
  }

  // BufferImpl -------------------------------------------------------------------------------------------------------

  BufferImpl::BufferImpl(Device device, vk::Buffer buffer, utils::allocator::Allocation allocation)
      : device_(std::move(device)), buffer_(buffer), allocation_(std::move(allocation))
  {
  }

  // DeviceLocalBufferImpl --------------------------------------------------------------------------------------------

  // HostLocalBufferImpl ----------------------------------------------------------------------------------------------

  void HostLocalBufferImpl::memCopy(void const* pData, utils::SizeT size, utils::OffsetT offset)
  {
    memCopyToBuffer(getDevice().getImpl()->getVkDevice(), getVkBuffer(), pData, size, offset);
  }

  // DeviceVisibleBufferImpl ------------------------------------------------------------------------------------------

  void DeviceVisibleBufferImpl::memCopy(void const* pData, utils::SizeT size, utils::OffsetT offset)
  {
    memCopyToBuffer(getDevice().getImpl()->getVkDevice(), getVkBuffer(), pData, size, offset);
  }

}  // namespace vulkan