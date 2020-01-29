#pragma once
#include <VEZ.h>
#include <utils/utils.hpp>
#include <vulkan/vulkan.hpp>
#include "../include/vulkan/core.hpp"

namespace vulkan
{
  void checkResult(VkResult result, std::string const& message = "vulkan fail");

  VezMemoryFlags toVkMemoryFlags(MemoryType type);

  vk::Extent3D toVkExtent(utils::Extent3D const& extent);

  vk::Offset3D toVkOffset(utils::Offset3D const& offset);

  vk::Extent2D toVkExtent(utils::Extent2D const& extent);

  vk::Offset2D toVkOffset(utils::Offset2D const& offset);

  vk::Offset2D toVkOffset(utils::Position2D const& offset);

  vk::Viewport toVkViewport(utils::Viewport const& viewport);

  vk::Rect2D toVkRect2D(utils::Rect2D const& rect);

  VkFormat toVkFormat(Format format);

  VkSampleCountFlagBits toVkSampleCount(SampleCountFlagBits sampleCount);

  VkCompareOp toVkCompareOp(CompareOp op);

  VkLogicOp toVkLogicOp(LogicOp op);

  VkBorderColor toVkBorderColor(BorderColor color);

  VkSamplerAddressMode toVkAddressMode(AddressMode mode);

  VkFilter toVkFilter(Filter filter);

  VkSamplerMipmapMode toVkMipMapMode(MipMapMode mode);

  vk::ComponentSwizzle toVkComponentSwizzle(ComponentSwizzle component);

  vk::ComponentMapping toVkComponentMapping(ComponentMapping const& components);

  VkPolygonMode toVkPolygonMode(PolygonMode mode);

  VkCullModeFlags toVkCullModeFlags(CullModeFlags const& cullMode);

  VkFrontFace toVkFrontFace(FrontFace frontFace);

  VkColorComponentFlags toVkColorComponentFlags(ColorComponentFlags flags);

  VkBlendFactor toVkBlendFactor(BlendFactor val);

  VkBlendOp toVkBlendOp(BlendOp blendOp);

}  // namespace vulkan