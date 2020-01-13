#pragma once
#include <vector>

namespace utils
{
  template <typename Bit_T, typename Mask_T = uint32_t>
  class BitFlags
  {
    template <typename T, typename MT>
    friend bool operator==(BitFlags<T, MT> const &lhs, BitFlags<T, MT> const &rhs);

   public:
    BitFlags() = default;

    BitFlags(Bit_T const &bit) noexcept : mask_(static_cast<Mask_T>(bit))
    {
    }

    explicit BitFlags(Mask_T const &flags) : mask_(flags)
    {
    }


    BitFlags &operator|=(BitFlags const &rhs) noexcept
    {
      mask_ |= rhs.mask_;
      return *this;
    }

    BitFlags &operator&=(BitFlags const &rhs) noexcept
    {
      mask_ &= rhs.mask_;
      return *this;
    }

    BitFlags &operator^=(BitFlags const &rhs) noexcept
    {
      mask_ ^= rhs.mask_;
      return *this;
    }

    explicit operator bool() const
    {
      return !!mask_;
    }

    explicit operator Mask_T() const
    {
      return mask_;
    }

   private:
    Mask_T mask_ = {};
  };

  template <typename T, typename MT>
  bool operator==(BitFlags<T, MT> const &lhs, BitFlags<T, MT> const &rhs)
  {
    return lhs.mask_ == rhs.mask_;
  }

  template <typename T, typename MT>
  bool operator!=(BitFlags<T, MT> const &lhs, BitFlags<T, MT> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T, typename MT>
  bool operator==(BitFlags<T, MT> const &lhs, T const &rhs)
  {
    return lhs == BitFlags<T, MT>(rhs);
  }

  template <typename T, typename MT>
  bool operator!=(BitFlags<T, MT> const &lhs, T const &rhs)
  {
    return lhs != BitFlags<T, MT>(rhs);
  }

  template <typename T, typename MT>
  bool operator==(T const &lhs, BitFlags<T, MT> const &rhs)
  {
    return BitFlags<T, MT>(lhs) == rhs;
  }

  template <typename T, typename MT>
  bool operator!=(T const &lhs, BitFlags<T, MT> const &rhs)
  {
    return BitFlags<T, MT>(lhs) != rhs;
  }

  template <typename T, typename MT>
  BitFlags<T, MT> operator|(BitFlags<T, MT> const &lhs, BitFlags<T, MT> const &rhs)
  {
    BitFlags<T, MT> result = lhs;
    result |= rhs;
    return result;
  }

  template <typename T, typename MT>
  BitFlags<T, MT> operator&(BitFlags<T, MT> const &lhs, BitFlags<T, MT> const &rhs)
  {
    BitFlags<T, MT> result = lhs;
    result &= rhs;
    return result;
  }

  template <typename T, typename MT>
  BitFlags<T, MT> operator^(BitFlags<T, MT> const &lhs, BitFlags<T, MT> const &rhs)
  {
    BitFlags<T, MT> result = lhs;
    result ^= rhs;
    return result;
  }

  template <typename T, typename MT>
  BitFlags<T, MT> operator|(BitFlags<T, MT> const &lhs, T const &rhs) noexcept
  {
    BitFlags<T, MT> result = lhs;
    result |= rhs;
    return result;
  }

  template <typename T, typename MT>
  BitFlags<T, MT> operator&(BitFlags<T, MT> const &lhs, T const &rhs) noexcept
  {
    BitFlags<T, MT> result = lhs;
    result &= rhs;
    return result;
  }

  template <typename T, typename MT>
  BitFlags<T, MT> operator^(BitFlags<T, MT> const &lhs, T const &rhs) noexcept
  {
    BitFlags<T, MT> result = lhs;
    result ^= rhs;
    return result;
  }

  template <typename T, typename MT>
  BitFlags<T, MT> operator|(T const &lhs, BitFlags<T, MT> const &rhs)
  {
    BitFlags<T, MT> result = lhs;
    result |= rhs;
    return result;
  }

  template <typename T, typename MT>
  BitFlags<T, MT> operator&(T const &lhs, BitFlags<T, MT> const &rhs)
  {
    BitFlags<T, MT> result = lhs;
    result &= rhs;
    return result;
  }

  template <typename T, typename MT>
  BitFlags<T, MT> operator^(T const &lhs, BitFlags<T, MT> const &rhs)
  {
    BitFlags<T, MT> result = lhs;
    result ^= rhs;
    return result;
  }
}  // namespace utils