#include "AllocatorPolitics.hpp"
#include <algorithm>
#include <cassert>

namespace utils::allocator
{
  // utils ------------------------------------------------------------------------------------------------------------

  AlignmentT offsetForAline(OffsetT offset, AlignmentT alignment)
  {
    if (alignment && offset % alignment)
    {
      return alignment - offset % alignment;
    }
    return 0;
  }

  bool canEmplace(std::pair<SizeT const, AllocInfo> const &alloc, SizeT size, OffsetT offset)
  {
    return alloc.second.is_empty && alloc.first >= size + offset;
  }

  OffsetT addAllocation(
      std::multimap<SizeT, AllocInfo> &allocations, SizeT &maxSize, SizeT size, AlignmentT alignment)
  {
    OffsetT alignedOffset = maxSize + offsetForAline(maxSize, alignment);
    allocations.emplace(size, AllocInfo{alignedOffset, false});
    maxSize = size + alignedOffset;
    return alignedOffset;
  }

  // DefaultAllocPolicy  -----------------------------------------------------------------------------------------------

  OffsetT DefaultAllocPolicy::allocate(SizeT size, AlignmentT alignment)
  {
    assert(size != 0 && "size cannot be equal to 0");

    // find empty slot that can contain allocation
    for (auto allocIter = allocations_.begin(); allocIter != allocations_.end(); ++allocIter)
    {
      OffsetT additionalOffset = offsetForAline(size, alignment);
      // if found, replace it
      if (canEmplace(*allocIter, size, additionalOffset))
      {
        auto allocSize = allocIter->first - additionalOffset;
        auto allocOffset = allocIter->second.offset + additionalOffset;

        allocIter = allocations_.erase(allocIter);
        allocations_.emplace(allocSize, AllocInfo{allocOffset, false});

        // update current size if required
        currentSize_ = std::max(allocOffset + allocSize, currentSize_);
        maxSize_ = std::max(maxSize_, currentSize_);
        return allocOffset;
      }
    }
    // if not found, add new slot
    auto allocOffset = addAllocation(allocations_, maxSize_, size, alignment);
    currentSize_ = maxSize_;
    return allocOffset;
  }

  void DefaultAllocPolicy::deallocate(OffsetT offset)
  {
    auto findIt = std::find_if(
        allocations_.begin(), allocations_.end(), [offset](auto const &val) { return val.second.offset == offset; });
    assert(findIt != allocations_.cend());
    findIt->second.is_empty = true;

    if (findIt->second.offset + findIt->first == currentSize_)
    {
      currentSize_ -= findIt->first;
    }
  }

  SizeT DefaultAllocPolicy::requiredExtension(SizeT size, AlignmentT alignment) const
  {
    for (auto &allocation : allocations_)
    {
      if (canEmplace(allocation, size, offsetForAline(size, alignment)))
      {
        auto maxAllocSize = allocation.first + allocation.second.offset;
        return maxAllocSize <= currentSize_ ? 0 :  maxAllocSize - currentSize_;
      }
    }
    return size + offsetForAline(maxSize_, alignment);
  }

}  // namespace utils::allocator