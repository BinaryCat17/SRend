#pragma once
#include "Allocator.hpp"

namespace utils::allocator
{
  // AllocatorImpl ----------------------------------------------------------------------------------------------------

  class AllocatorImpl
  {
   public:
    virtual ~AllocatorImpl() = default;

    virtual OffsetT allocate(SizeT size, AlignmentT alignment) = 0;

    virtual void deallocate(OffsetT offset) = 0;

    [[nodiscard]] virtual SizeT size() const = 0;

    [[nodiscard]] virtual SizeT requiredExtension(SizeT size, AlignmentT alignment) const = 0;
  };

  // AllocationImpl ---------------------------------------------------------------------------------------------------

  class AllocationImpl
  {
   public:
    AllocationImpl(std::shared_ptr<AllocatorImpl> policy, SizeT size, AlignmentT alignment)
        : policy_(std::move(policy)), size_(size), offset_(policy_->allocate(size, alignment))
    {
    }

    ~AllocationImpl()
    {
      policy_->deallocate(offset_);
    }

    [[nodiscard]] SizeT size() const
    {
      return size_;
    }

    [[nodiscard]] OffsetT offset() const
    {
      return offset_;
    }

   private:
    std::shared_ptr<AllocatorImpl> policy_;
    SizeT size_;
    OffsetT offset_;
  };

}  // namespace utils::allocator