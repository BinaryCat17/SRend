#pragma once
#include <VEZ.h>
#include <utils/utils.hpp>
#include <vulkan/vulkan.hpp>
#include "../include/vulkan/core.hpp"

namespace vulkan
{
  void checkResult(VkResult result, std::string const& message = "vulkan fail");

  template <typename ImplT, typename T>
  auto implCast(T ptr)
  {
    return std::dynamic_pointer_cast<ImplT>(ptr);
  }

  vk::Extent3D toVkExtent(utils::Extent3D const& extent);

  vk::Offset3D toVkOffset(utils::Offset3D const& offset);

  vk::Viewport toVkViewport(utils::Viewport const& viewport);

  vk::Rect2D toVkRect2D(utils::Rect2D const& rect);

  vk::Format toVkFormat(Format format);

  vk::SampleCountFlagBits toVkSampleCount(SampleCountFlagBits sampleCount);

  vk::CompareOp toVkCompareOp(CompareOp op);

  vk::LogicOp toVkLogicOp(LogicOp op);

}  // namespace vulkan