#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(BufferCreate, {};)

  // clang-format on

  // Buffer -----------------------------------------------------------------------------------------------------------

  class Buffer
  {
   public:
    virtual ~Buffer() = default;

    [[nodiscard]] virtual utils::SizeT size() const = 0;
  };

  // DeviceLocalBuffer ------------------------------------------------------------------------------------------------

  class DeviceLocalBuffer : public virtual Buffer
  {
   public:
  };

  std::shared_ptr<DeviceLocalBuffer> createDeviceLocalBuffer(
      Device const& device, BufferCreateFlags const& createFlags, utils::SizeT size, utils::AlignmentT alignment);

  // HostLocalBuffer --------------------------------------------------------------------------------------------------

  class HostLocalBuffer : public virtual Buffer
  {
   public:
    virtual void memCopy(void const* pData, utils::SizeT size, utils::OffsetT offset) = 0;
  };

  std::shared_ptr<HostLocalBuffer> createHostLocalBuffer(
      Device const& device, BufferCreateFlags const& createFlags, utils::SizeT size, utils::AlignmentT alignment);

  std::shared_ptr<HostLocalBuffer> createStagingBuffer(
      Device const& device, BufferCreateFlags const& createFlags, utils::SizeT size, utils::AlignmentT alignment);

  // DeviceVisibleBuffer ----------------------------------------------------------------------------------------------

  class DeviceVisibleBuffer : public HostLocalBuffer, public DeviceLocalBuffer
  {
   public:
  };

  std::shared_ptr<DeviceVisibleBuffer> createDeviceVisibleBuffer(
      Device const& device, BufferCreateFlags const& createFlags, utils::SizeT size, utils::AlignmentT alignment);

}  // namespace vulkan