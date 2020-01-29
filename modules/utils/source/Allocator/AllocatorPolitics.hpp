#pragma once
#include <map>
#include "AllocatorImpl.hpp"

namespace utils::allocator
{
  // utils ------------------------------------------------------------------------------------------------------------

  struct AllocInfo
  {
    OffsetT offset;
    bool is_empty;
  };

  using AllocIter = std::multimap<SizeT, AllocInfo>::iterator;

  // DefaultAllocPolicy -----------------------------------------------------------------------------------------------

  class DefaultAllocPolicy : public AllocatorImpl
  {
   public:
    OffsetT allocate(SizeT size, AlignmentT alignment) override;

    void deallocate(OffsetT offset) override;

    [[nodiscard]] SizeT size() const override
    {
      return currentSize_;
    }

    [[nodiscard]] SizeT requiredExtension(SizeT size, AlignmentT alignment) const override;

   private:
    std::multimap<SizeT, AllocInfo> allocations_;
    SizeT currentSize_ = 0;
    SizeT maxSize_ = 0;
  };

}  // namespace utils::allocator