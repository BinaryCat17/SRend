#include "utils.hpp"

namespace vulkan
{
  void checkResult(VkResult result, std::string const& message)
  {
    if (result != VK_SUCCESS)
    {
      vk::throwResultException(static_cast<vk::Result>(result), message.c_str());
    }
  }

  VezMemoryFlags toVkMemoryFlags(MemoryType type)
  {
    switch (type)
    {
      case MemoryType::DeviceLocal:
        return VEZ_MEMORY_GPU_ONLY;
      case MemoryType::HostLocal:
        return VEZ_MEMORY_CPU_ONLY;
      case MemoryType::HostToDivice:
        return VEZ_MEMORY_CPU_TO_GPU;
      case MemoryType::DeviceToHost:
        return VEZ_MEMORY_GPU_TO_CPU;
    }
    throw std::runtime_error("undefined memory flags");
  }

  vk::Extent3D toVkExtent(utils::Extent3D const& extent)
  {
    return VkExtent3D{extent.width(), extent.height(), extent.depth()};
  }

  vk::Offset3D toVkOffset(utils::Offset3D const& offset)
  {
    return vk::Offset3D(offset.x(), offset.y(), offset.z());
  }

  vk::Extent2D toVkExtent(utils::Extent2D const& extent)
  {
    return VkExtent2D{extent.width(), extent.height()};
  }

  vk::Offset2D toVkOffset(utils::Offset2D const& offset)
  {
    return vk::Offset2D(offset.x(), offset.y());
  }

  vk::Offset2D toVkOffset(utils::Position2D const& offset)
  {
    return vk::Offset2D(offset.x(), offset.y());
  }

  VkFormat toVkFormat(Format format)
  {
    return static_cast<VkFormat>(format);
  }

  VkSampleCountFlagBits toVkSampleCount(SampleCountFlagBits sampleCount)
  {
    return static_cast<VkSampleCountFlagBits>(sampleCount);
  }

  VkCompareOp toVkCompareOp(CompareOp op)
  {
    return static_cast<VkCompareOp>(op);
  }

  VkLogicOp toVkLogicOp(LogicOp op)
  {
    return static_cast<VkLogicOp>(op);
  }

  vk::Viewport toVkViewport(utils::Viewport const& viewport)
  {
    return vk::Viewport(
        viewport.x(), viewport.y(), viewport.width(), viewport.height(), viewport.minDepth(), viewport.maxDepth());
  }

  vk::Rect2D toVkRect2D(utils::Rect2D const& rect)
  {
    vk::Rect2D vkRect({static_cast<int32_t>(rect.x()), static_cast<int32_t>(rect.y())}, {rect.width(), rect.height()});
    return vkRect;
  }

  VkBorderColor toVkBorderColor(BorderColor color)
  {
    return static_cast<VkBorderColor>(color);
  }

  VkSamplerAddressMode toVkAddressMode(AddressMode mode)
  {
    return static_cast<VkSamplerAddressMode>(mode);
  }

  VkFilter toVkFilter(Filter filter)
  {
    return static_cast<VkFilter>(filter);
  }

  VkSamplerMipmapMode toVkMipMapMode(MipMapMode mode)
  {
    return static_cast<VkSamplerMipmapMode>(mode);
  }

  vk::ComponentSwizzle toVkComponentSwizzle(ComponentSwizzle component)
  {
    return static_cast<vk::ComponentSwizzle>(component);
  }

  vk::ComponentMapping toVkComponentMapping(ComponentMapping const& components)
  {
    return vk::ComponentMapping(toVkComponentSwizzle(components.r), toVkComponentSwizzle(components.g),
                                toVkComponentSwizzle(components.b), toVkComponentSwizzle(components.a));
  }

  VkPolygonMode toVkPolygonMode(PolygonMode mode)
  {
    return static_cast<VkPolygonMode>(mode);
  }

  VkCullModeFlags toVkCullModeFlags(CullModeFlags const& cullMode)
  {
    return static_cast<VkCullModeFlags>(static_cast<VkCullModeFlags>(cullMode));
  }

  VkFrontFace toVkFrontFace(FrontFace frontFace)
  {
    return static_cast<VkFrontFace>(frontFace);
  }

  VkColorComponentFlags toVkColorComponentFlags(ColorComponentFlags flags)
  {
    return static_cast<VkColorComponentFlags>(flags);
  }

  VkBlendFactor toVkBlendFactor(BlendFactor val)
  {
    return static_cast<VkBlendFactor>(val);
  }

  VkBlendOp toVkBlendOp(BlendOp blendOp)
  {
    return static_cast<VkBlendOp>(blendOp);
  }

}  // namespace vulkan