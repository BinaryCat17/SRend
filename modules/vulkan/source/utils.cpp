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

  vk::Extent3D toVkExtent(utils::Extent3D const& extent)
  {
    return VkExtent3D{extent.width(), extent.height(), extent.depth()};
  }

  vk::Offset3D toVkOffset(utils::Offset3D const& offset)
  {
    return vk::Offset3D(offset.x(), offset.y(), offset.z());
  }

  vk::Format toVkFormat(Format format)
  {
    return static_cast<vk::Format>(format);
  }

  vk::SampleCountFlagBits toVkSampleCount(SampleCountFlagBits sampleCount)
  {
    return static_cast<vk::SampleCountFlagBits>(sampleCount);
  }

  vk::CompareOp toVkCompareOp(CompareOp op)
  {
    return static_cast<vk::CompareOp>(op);
  }

  vk::LogicOp toVkLogicOp(LogicOp op)
  {
    return static_cast<vk::LogicOp>(op);
  }

  vk::Viewport toVkViewport(utils::Viewport const& viewport)
  {
    return vk::Viewport(viewport.x(), viewport.y(), viewport.width(), viewport.height());
  }

  vk::Rect2D toVkRect2D(utils::Rect2D const& rect)
  {
    return vk::Rect2D({static_cast<int32_t>(rect.x(), static_cast<int32_t>(rect.y()))}, {rect.width(), rect.height()});
  }

}  // namespace vulkan