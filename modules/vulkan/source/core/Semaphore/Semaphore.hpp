#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // Semaphore --------------------------------------------------------------------------------------------------------

  class SemaphoreImpl;

  class Semaphore
  {
   public:
    explicit Semaphore(std::shared_ptr<SemaphoreImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<SemaphoreImpl> getImpl() const
    {
      return pimpl_;
    }

   private:
    std::shared_ptr<SemaphoreImpl> pimpl_;
  };

}  // namespace vulkan
