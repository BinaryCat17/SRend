#include "Buffer.hpp"
#include "../PhysicalDevice/PhysicalDevice.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  vulkan::BufferManager& selectBufferManager(vulkan::DeviceImpl& device, MemoryType memoryType)
  {
    auto& deviceBuffers = device.getBuffers();

    switch (memoryType)
    {
      case MemoryType::DeviceLocal:
        return deviceBuffers.deviceLocalManager;
      case MemoryType::HostLocal:
        return deviceBuffers.hostToDeviceManager;
      case MemoryType::DeviceToHost:
        return deviceBuffers.deviceToHostManager;
      case MemoryType::HostToDivice:
        return deviceBuffers.hostToDeviceManager;
    }

    throw std::runtime_error("undefined memory type");
  }

  utils::AlignmentT requiredAlignment(vulkan::DeviceImpl const& device, BufferUsageFlags const& usage)
  {
    utils::AlignmentT alignment = 0;
    vk::PhysicalDeviceLimits limits = device.getPhysicalDevice()->getVkPhysicalDevice().getProperties().limits;

    if (usage & vulkan::BufferUsageFlagBits::UniformBuffer)
    {
      alignment = limits.minUniformBufferOffsetAlignment;
    }

    if (usage & vulkan::BufferUsageFlagBits::VertexBuffer)
    {
      alignment = 8;
    }

    return alignment;
  }

  // BufferImpl -------------------------------------------------------------------------------------------------------

  BufferImpl::BufferImpl(std::shared_ptr<DeviceImpl> device, BufferCreateFlags const&, MemoryType memoryType,
      BufferUsageFlags const& usage, utils::SizeT size)
      : device_(std::move(device)), allocation_(nullptr)
  {
    std::tie(vkBuffer_, allocation_) =
        selectBufferManager(*device_, memoryType).allocate(size, requiredAlignment(*device_, usage));
  }

  void* BufferImpl::mapMemory(utils::SizeT size, utils::OffsetT offset)
  {
    void* pMappedData = nullptr;
    vezMapBuffer(device_->getVkDevice(), vkBuffer_, allocation_.offset() + offset, size, &pMappedData);
    return reinterpret_cast<char*>(pMappedData) + allocation_.offset() + offset;
  }

  void BufferImpl::unmapMemory()
  {
    vezUnmapBuffer(device_->getVkDevice(), vkBuffer_);
  }

  // Buffer -----------------------------------------------------------------------------------------------------------

  Buffer::Buffer(Device const& device, BufferCreateFlags const& createFlags, BufferUsageFlags const& usage,
      utils::SizeT size, MemoryType memoryType)
      : pimpl_(std::make_shared<BufferImpl>(device.getImpl(), createFlags, memoryType, usage, size))
  {
  }

  utils::SizeT Buffer::getSize() const noexcept
  {
    return pimpl_->size();
  }

  [[nodiscard]] BufferMappedData Buffer::mapMemory(utils::SizeT size, utils::OffsetT offset)
  {
    return BufferMappedData(std::make_shared<BufferMappedDataImpl>(pimpl_, size, offset));
  }

  // BufferMappedDataImpl ---------------------------------------------------------------------------------------------

  [[nodiscard]] void* BufferMappedData::pData() noexcept
  {
    return pimpl_->pData();
  }

  [[nodiscard]] void const* BufferMappedData::pData() const noexcept
  {
    return pimpl_->pData();
  }

  void BufferMappedData::unmap()
  {
    return pimpl_->unmap();
  }

}  // namespace vulkan