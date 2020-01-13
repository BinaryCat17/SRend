#pragma once
#include <vulkan/vulkan.hpp>

namespace vulkan
{
  class SemaphoreImpl
  {
   public:
    explicit SemaphoreImpl(vk::Semaphore vkSemaphore) : vkSemaphore_(vkSemaphore)
    {
    }

    [[nodiscard]] vk::Semaphore getVkSemaphore() const
    {
      return vkSemaphore_;
    }

   private:
    vk::Semaphore vkSemaphore_;
  };

}  // namespace vulkan
