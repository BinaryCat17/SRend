#pragma once
#include <iosfwd>
#include <magic_enum.hpp>
#include "BitFlags.hpp"

#define SR_MAKE_BIT_FLAGS(name, ...)                                                              \
  enum class name##FlagBits __VA_ARGS__ using name##Flags = ::utils::BitFlags<name##FlagBits>;    \
  inline ::utils::BitFlags<name##FlagBits> operator|(name##FlagBits a, name##FlagBits b) noexcept \
  {                                                                                               \
    return ::utils::BitFlags<name##FlagBits>(a) | b;                                              \
  }

namespace utils
{
  template <typename Enum_T, typename FlagT>
  std::string flagsToString(BitFlags<Enum_T, FlagT> value)
  {
    std::string result;
    for (auto val : magic_enum::enum_values<Enum_T>())
    {
      if (val & value)
      {
        result += magic_enum::enum_name(val);
        result += " ";
      }
    }
    if (!result.empty())
    {
      result.pop_back();
    }
    return result;
  }

  template <typename Enum_T>
  std::string flagsToString(Enum_T value)
  {
    std::string result;
    for (auto val : magic_enum::enum_values<Enum_T>())
    {
      if (val & value)
      {
        result += magic_enum::enum_name(val);
        result += " ";
      }
    }
    if (!result.empty())
    {
      result.pop_back();
    }
    return result;
  }

  template <typename Enum_T, typename FlagT>
  std::ostream &operator<<(std::ostream &os, BitFlags<Enum_T, FlagT> value)
  {
    os << flagsToString(value);
    return os;
  }
}  // namespace utils