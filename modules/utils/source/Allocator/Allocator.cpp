#include "Allocator.hpp"
#include "AllocatorImpl.hpp"
#include "AllocatorPolitics.hpp"

namespace utils::allocator
{
  // utils ------------------------------------------------------------------------------------------------------------

  std::shared_ptr<AllocatorImpl> createAllocatorImpl(AllocatorCreateFlags, AllocatorPolicy policy)
  {
    switch (policy)
    {
      case AllocatorPolicy::Default:
        return std::make_shared<DefaultAllocPolicy>();
      default:
        throw std::runtime_error("undefined allocator policy");
    }
  }

  // Allocation -------------------------------------------------------------------------------------------------------

  SizeT Allocation::size() const
  {
    return pimpl_->size();
  }

  OffsetT Allocation::offset() const
  {
    return pimpl_->offset();
  }

  // Allocator --------------------------------------------------------------------------------------------------------

  Allocator::Allocator(AllocatorCreateFlags createFlags, AllocatorPolicy policy)
      : pimpl_(createAllocatorImpl(createFlags, policy))
  {
  }

  Allocator::Allocator() : Allocator(AllocatorCreateFlags{})
  {
  }

  Allocation Allocator::allocate(SizeT size, AlignmentT alignment)
  {
    return Allocation(std::make_shared<AllocationImpl>(pimpl_, size, alignment));
  }

  SizeT Allocator::requiredExtension(SizeT size, AlignmentT alignment) const
  {
    return pimpl_->requiredExtension(size, alignment);
  }

  SizeT Allocator::size() const
  {
    return pimpl_->size();
  }

}  // namespace utils::allocator
