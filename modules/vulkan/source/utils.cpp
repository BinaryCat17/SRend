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
}  // namespace vulkan