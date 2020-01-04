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
    if (alloc.second.is_empty)
    {
      if (alloc.first >= size + offset)
      {
        return true;
      }
    }
    return false;
  }

  OffsetT addAllocation(std::map<SizeT, AllocInfo> &allocations, SizeT &currentSize, SizeT size, AlignmentT alignment)
  {
    OffsetT alignedOffset = currentSize + offsetForAline(currentSize, alignment);
    allocations.emplace(size, AllocInfo{alignedOffset, false});
    currentSize = size + alignedOffset;
    return alignedOffset;
  }

  // DefaultAllocPolicy -----------------------------------------------------------------------------------------------

  OffsetT DefaultAllocPolicy::allocate(SizeT size, AlignmentT alignment)
  {
    for (auto &allocation : allocations_)
    {
      OffsetT offset = offsetForAline(size, alignment);
      if (canEmplace(allocation, size, offset))
      {
        allocation.second.is_empty = false;
        allocation.second.offset += offset;
        return allocation.second.offset;
      }
    }
    return addAllocation(allocations_, current_size_, size, alignment);
  }

  void DefaultAllocPolicy::deallocate(OffsetT offset)
  {
    auto findIt = std::find_if(
        allocations_.begin(), allocations_.end(), [offset](auto const &val) { return val.second.offset == offset; });
    assert(findIt != allocations_.cend());
    findIt->second.is_empty = true;

    if (findIt == --allocations_.begin())
    {
      current_size_ -= findIt->first;
    }
  }

  SizeT DefaultAllocPolicy::requiredExtension(SizeT size, AlignmentT alignment) const
  {
    for (auto &allocation : allocations_)
    {
      if (canEmplace(allocation, size, offsetForAline(size, alignment)))
      {
        return 0;
      }
    }
    return size + offsetForAline(current_size_, alignment);
  }

}  // namespace utils::allocator