#include <utils/allocator.hpp>
#include "../Device/Device.hpp"

namespace vulkan
{
  // BufferImpl -------------------------------------------------------------------------------------------------------

  class BufferImpl
  {
   public:
    BufferImpl(std::shared_ptr<DeviceImpl> device, BufferCreateFlags const& createFlags, MemoryType memoryType,
        BufferUsageFlags const& usage, utils::SizeT size, utils::AlignmentT alignment);

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

}  // namespace vulkan