#pragma once
#include <VEZ.h>
#include <vulkan/vulkan.hpp>

namespace vulkan
{
  void checkResult(VkResult result, std::string const& message = "vulkan fail");

  template <typename ImplT, typename T>
  auto implCast(T ptr)
  {
    return std::dynamic_pointer_cast<ImplT>(ptr);
  }

}  // namespace vulkan