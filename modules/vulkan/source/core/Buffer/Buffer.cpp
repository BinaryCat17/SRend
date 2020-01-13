#include "Buffer.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  // BufferImpl -------------------------------------------------------------------------------------------------------

  BufferImpl::BufferImpl(std::shared_ptr<DeviceImpl> device, BufferCreateFlags const&, MemoryType memoryType,
      BufferUsageFlags const&, utils::SizeT size, utils::AlignmentT alignment)
      : device_(std::move(device)), allocation_(nullptr)
  {
    std::pair<vk::Buffer, utils::allocator::Allocation> alloc(nullptr, nullptr);

    switch (memoryType)
    {
      case MemoryType::DeviceLocal:
        alloc = device->getBuffers().deviceLocalManager.allocate(size, alignment);
        break;
      case MemoryType::HostLocal:
        alloc = device->getBuffers().hostLocalManager.allocate(size, alignment);
        break;
      case MemoryType::DeviceToHost:
        alloc = device->getBuffers().deviceToHostManager.allocate(size, alignment);
        break;
      case MemoryType::HostToDivice:
        alloc = device->getBuffers().hostToDeviceManager.allocate(size, alignment);
        break;
    }

    vkBuffer_ = alloc.first;
    allocation_ = alloc.second;
  }

  void* BufferImpl::mapMemory(utils::SizeT size, utils::OffsetT offset)
  {
    void* pMappedData = nullptr;
    vezMapBuffer(device_->getVkDevice(), vkBuffer_, offset, size, &pMappedData);
    return pMappedData;
  }

  void BufferImpl::unmapMemory()
  {
    vezUnmapBuffer(device_->getVkDevice(), vkBuffer_);
  }

  // Buffer -----------------------------------------------------------------------------------------------------------

  utils::SizeT Buffer::getSize() const
  {
    return pimpl_->size();
  }

  [[nodiscard]] void* Buffer::mapMemory(utils::SizeT size, utils::OffsetT offset)
  {
    return pimpl_->mapMemory(size, offset);
  }

  void Buffer::unmapMemory()
  {
    pimpl_->unmapMemory();
  }

}  // namespace vulkan