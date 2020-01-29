#include "utils.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace render
{
  void memCopyToBuffer(vulkan::Buffer& buffer, void const* pData, utils::SizeT size)
  {
    if (pData)
    {
      auto mappedData = buffer.mapMemory(size);
      memcpy(mappedData.pData(), pData, size);
    }
  }

  vulkan::Buffer createHostLocalBuffer(
      vulkan::Device& device, vulkan::BufferUsageFlags const& usage, void const* pData, utils::SizeT size)
  {
    vulkan::Buffer buffer(device, {}, usage, size, vulkan::MemoryType::HostLocal);
    memCopyToBuffer(buffer, pData, size);
    return buffer;
  }


  vulkan::Buffer createStagingBuffer(vulkan::Device& device, void const* pData, utils::SizeT size)
  {
    vulkan::Buffer stagingBuffer(
        device, {}, vulkan::BufferUsageFlagBits::TransferSrc, size, vulkan::MemoryType::HostLocal);
    memCopyToBuffer(stagingBuffer, pData, size);

    return stagingBuffer;
  }

  void stagingFillBuffer(vulkan::Device& device, vulkan::Buffer& buffer, void const* pData, utils::SizeT size)
  {
    if (pData)
    {
      auto stagingBuffer = createStagingBuffer(device, pData, size);

      vulkan::CommandBuffer transferCommandBuffer(device, {}, vulkan::CommandBufferType::Transfer);
      transferCommandBuffer.begin(vulkan::CommandBufferBeginFlagBits::OneTimeSubmit);
      transferCommandBuffer.copyBuffer(stagingBuffer, buffer);
      transferCommandBuffer.submit({});
    }
  }

  vulkan::Buffer createDeviceBuffer(
      vulkan::Device& device, vulkan::BufferUsageFlags const& usage, void const* pData, utils::SizeT size)
  {
    vulkan::Buffer buffer(
        device, {}, vulkan::BufferUsageFlagBits::TransferDst | usage, size, vulkan::MemoryType::DeviceLocal);
    stagingFillBuffer(device, buffer, pData, size);
    return buffer;
  }

  vulkan::Buffer createUniformBuffer(vulkan::Device& device, void const* pData, utils::SizeT size)
  {
    return createHostToDeviceBuffer(device, vulkan::BufferUsageFlagBits::UniformBuffer, pData, size);
  }

  vulkan::Buffer createHostToDeviceBuffer(
      vulkan::Device& device, vulkan::BufferUsageFlags const& usage, void const* pData, utils::SizeT size)
  {
    vulkan::Buffer buffer(device, {}, usage, size, vulkan::MemoryType::HostToDivice);
    memCopyToBuffer(buffer, pData, size);
    return buffer;
  }

  void stagingFillImage(vulkan::Device& device, vulkan::Image& image, void const* pData, utils::SizeT size)
  {
    if (pData)
    {
      auto stagingBuffer = createStagingBuffer(device, pData, size);
      vulkan::CommandBuffer commandBuffer(device, {}, vulkan::CommandBufferType::Transfer);
      commandBuffer.begin(vulkan::CommandBufferBeginFlagBits::OneTimeSubmit);
      commandBuffer.copyBufferToImage(stagingBuffer, image);
      commandBuffer.submit();
    }
  }

  vulkan::Image createDeviceImage(vulkan::Device& device, utils::Extent3D const& extent, vulkan::Format format,
      vulkan::ImageUsageFlags const& usage, void const* pData, utils::SizeT size)
  {
    vulkan::Image image(device, {}, extent, format, usage | vulkan::ImageUsageFlagBits::TransferDst);
    stagingFillImage(device, image, pData, size);
    return image;
  }

  vulkan::Image createSampledImage(vulkan::Device& device, utils::Extent3D const& extent, vulkan::Format format,
      void const* pData, utils::SizeT size)
  {
    return createDeviceImage(device, extent, format, vulkan::ImageUsageFlagBits::Sampled, pData, size);
  }

  glm::mat4 createTransformMatrix(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale)
  {
    glm::mat4 transform = glm::mat4(1);

    transform = glm::translate(transform, pos);
    transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1,0,0));
    transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0,1,0));
    transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0,0,1));
    transform = glm::scale(transform, scale);

    return transform;
  }

}  // namespace render
