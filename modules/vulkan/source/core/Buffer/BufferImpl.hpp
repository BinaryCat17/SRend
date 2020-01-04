#include <utils/allocator.hpp>
#include "../Device/DeviceImpl.hpp"
#include "Buffer.hpp"

namespace vulkan
{
  // BufferImpl -------------------------------------------------------------------------------------------------------

  class BufferImpl : public virtual Buffer
  {
   public:
    BufferImpl(Device device, vk::Buffer buffer, utils::allocator::Allocation allocation);

    [[nodiscard]] Device const& getDevice() const
    {
      return device_;
    }

    [[nodiscard]] vk::Buffer getVkBuffer() const
    {
      return buffer_;
    }

    [[nodiscard]] utils::OffsetT offset() const
    {
      return allocation_.offset();
    }

    [[nodiscard]] utils::SizeT size() const override
    {
      return allocation_.size();
    }

   private:
    Device device_;
    vk::Buffer buffer_;
    utils::allocator::Allocation allocation_;
  };

  // DeviceLocalBufferImpl --------------------------------------------------------------------------------------------

  class DeviceLocalBufferImpl : public virtual DeviceLocalBuffer, public virtual BufferImpl
  {
   public:
    using BufferImpl::BufferImpl;
  };

  // HostLocalBufferImpl --------------------------------------------------------------------------------------------

  class HostLocalBufferImpl : public virtual HostLocalBuffer, public virtual BufferImpl
  {
   public:
    using BufferImpl::BufferImpl;

    void memCopy(void const* pData, utils::SizeT size, utils::OffsetT offset) override;
  };

  // DeviceVisibleBufferImpl ------------------------------------------------------------------------------------------

  class DeviceVisibleBufferImpl : public DeviceVisibleBuffer, public BufferImpl
  {
   public:
    using BufferImpl::BufferImpl;

    void memCopy(void const* pData, utils::SizeT size, utils::OffsetT offset) override;
  };

}  // namespace vulkan