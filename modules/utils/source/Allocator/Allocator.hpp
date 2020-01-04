#pragma once
#include <memory>
#include "../flagsUtils/flagsUtils.hpp"
#include "../utilTypes/utilTypes.hpp"

namespace utils::allocator
{
  // utils ------------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(AllocatorCreate, {};)

  // clang-format on

  enum class AllocatorPolicy
  {
    Default
  };

  // Allocation -------------------------------------------------------------------------------------------------------

  class AllocationImpl;

  class Allocation
  {
   public:
    explicit Allocation(std::shared_ptr<AllocationImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<AllocationImpl> getImpl() const
    {
      return pimpl_;
    }

    [[nodiscard]] SizeT size() const;

    [[nodiscard]] OffsetT offset() const;

   private:
    std::shared_ptr<AllocationImpl> pimpl_;
  };

  // Allocator --------------------------------------------------------------------------------------------------------

  class AllocatorImpl;

  class Allocator
  {
   public:
    explicit Allocator(std::shared_ptr<AllocatorImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<AllocatorImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit Allocator(AllocatorCreateFlags createFlags, AllocatorPolicy policy = AllocatorPolicy::Default);

    Allocator();

    Allocation allocate(SizeT size, AlignmentT alignment = 0);

    [[nodiscard]] SizeT requiredExtension(SizeT size, AlignmentT alignment) const;

    [[nodiscard]] SizeT size() const;

   private:
    std::shared_ptr<AllocatorImpl> pimpl_;
  };

}  // namespace utils::allocator