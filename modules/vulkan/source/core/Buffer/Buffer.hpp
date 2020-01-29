#include <utils/allocator.hpp>
#include "../Device/Device.hpp"

namespace vulkan
{
  // BufferImpl -------------------------------------------------------------------------------------------------------

  class BufferImpl
  {
   public:
    BufferImpl(std::shared_ptr<DeviceImpl> device, BufferCreateFlags const& createFlags, MemoryType memoryType,
        BufferUsageFlags const& usage, utils::SizeT size);

    BufferImpl(BufferImpl const&) = delete;

    BufferImpl(BufferImpl&&) = delete;

    BufferImpl& operator=(BufferImpl const&) = delete;

    BufferImpl& operator=(BufferImpl&&) = delete;

    [[nodiscard]] std::shared_ptr<DeviceImpl> const& getDevice() const
    {
      return device_;
    }

    [[nodiscard]] vk::Buffer getVkBuffer() const
    {
      return vkBuffer_;
    }

    [[nodiscard]] utils::OffsetT offset() const
    {
      return allocation_.offset();
    }

    [[nodiscard]] utils::SizeT size() const
    {
      return allocation_.size();
    }

    [[nodiscard]] void* mapMemory(utils::SizeT size, utils::OffsetT offset = 0);

    void unmapMemory();
   private:
    std::shared_ptr<DeviceImpl> device_;
    vk::Buffer vkBuffer_;
    utils::allocator::Allocation allocation_;
  };

  // BufferMappedDataImpl ---------------------------------------------------------------------------------------------

  class BufferMappedDataImpl
  {
   public:
    explicit BufferMappedDataImpl(std::shared_ptr<BufferImpl> buffer, utils::SizeT size, utils::OffsetT offset)
        : buffer_(std::move(buffer)), mappedData_(buffer_->mapMemory(size, offset))
    {
    }

    BufferMappedDataImpl(BufferMappedDataImpl const&) = delete;

    BufferMappedDataImpl(BufferMappedDataImpl&&) = delete;

    BufferMappedDataImpl& operator=(BufferMappedDataImpl const&) = delete;

    BufferMappedDataImpl& operator=(BufferMappedDataImpl&&) = delete;

    ~BufferMappedDataImpl()
    {
      unmap();
    }

    [[nodiscard]] void* pData() noexcept
    {
      return mappedData_;
    }

    [[nodiscard]] void const* pData() const noexcept
    {
      return mappedData_;
    }

    void unmap()
    {
      buffer_->unmapMemory();
    }

   private:
    std::shared_ptr<BufferImpl> buffer_;
    void* mappedData_;
  };

}  // namespace vulkan