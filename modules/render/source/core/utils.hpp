#pragma once
#include "../../include/render/core.hpp"

namespace render
{
  void memCopyToBuffer(vulkan::Buffer& buffer, void const* pData, utils::SizeT size);

  vulkan::Buffer createHostLocalBuffer(
      vulkan::Device& device, vulkan::BufferUsageFlags const& usage, void const* pData, utils::SizeT size);

  vulkan::Buffer createStagingBuffer(vulkan::Device& device, void const* pData, utils::SizeT size);

  void stagingFillBuffer(vulkan::Device& device, vulkan::Buffer& buffer, void const* pData, utils::SizeT size);

  vulkan::Buffer createDeviceBuffer(
      vulkan::Device& device, vulkan::BufferUsageFlags const& usage, void const* pData, utils::SizeT size);

  vulkan::Buffer createHostToDeviceBuffer(
      vulkan::Device& device, vulkan::BufferUsageFlags const& usage, void const* pData, utils::SizeT size);

  vulkan::Buffer createUniformBuffer(vulkan::Device& device, void const* pData, utils::SizeT size);

  void stagingFillImage(vulkan::Device& device, vulkan::Image& image, void const* pData, utils::SizeT size);

  vulkan::Image createDeviceImage(vulkan::Device& device, utils::Extent3D const& extent, vulkan::Format format,
      vulkan::ImageUsageFlags const& usage, void const* pData, utils::SizeT size);

  vulkan::Image createSampledImage(vulkan::Device& device, utils::Extent3D const& extent, vulkan::Format format,
      void const* pData, utils::SizeT size);

  glm::mat4 createTransformMatrix(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale);

}  // namespace render