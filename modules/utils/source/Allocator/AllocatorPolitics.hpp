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

  // DefaultAllocPolicy -----------------------------------------------------------------------------------------------

  class DefaultAllocPolicy : public AllocatorImpl
  {
   public:
    OffsetT allocate(SizeT size, AlignmentT alignment) override;

    void deallocate(OffsetT offset) override;

    [[nodiscard]] SizeT size() const override
    {
      return current_size_;
    }

    [[nodiscard]] SizeT requiredExtension(SizeT size, AlignmentT alignment) const override;

   private:
    std::map<SizeT, AllocInfo> allocations_;
    SizeT current_size_ = 0;
  };

}  // namespace utils::allocator