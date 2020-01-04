#include "Version.hpp"
#include <iostream>

namespace utils
{
  // VersionListTraits ------------------------------------------------------------------------------------------------

  // VersionTraits<unsigned>

  unsigned VersionListTraits<unsigned>::toUint(std::vector<unsigned> const &vec)
  {
    unsigned result = 0;
    for (unsigned const i : vec)
    {
      (result *= 10) += i;
    }
    return result;
  }

  std::string VersionListTraits<unsigned>::toString(std::vector<unsigned> const &vec)
  {
    std::string result;
    for (unsigned const val : vec)
    {
      result += std::to_string(val) + ".";
    }
    result.pop_back();
    return result;
  }

  std::istream &VersionListTraits<unsigned>::read(std::istream &is, std::vector<unsigned> &vec)
  {
    for (unsigned val = 0; is >> val;)
    {
      vec.push_back(val);

      if (is.get() != '.')
      {
        break;
      }
    }
    return is;
  }

  std::ostream &VersionListTraits<unsigned>::print(std::ostream &os, std::vector<unsigned> const &vec)
  {
    for (auto val : vec)
    {
      os << val;
    }
    return os;
  }

  bool VersionListTraits<unsigned>::equal(std::vector<unsigned> const &lhs, std::vector<unsigned> const &rhs)
  {
    return lhs == rhs;
  }

  bool VersionListTraits<unsigned>::less(std::vector<unsigned> const &lhs, std::vector<unsigned> const &rhs)
  {
    return toUint(lhs) < toUint(rhs);
  }

  // VersionTraits<unsigned char>

  unsigned VersionListTraits<char>::toUint(std::vector<char> const &vec)
  {
    unsigned result = 0;
    for (char const i : vec)
    {
      if (isdigit(i))
      {
        (result *= 10) += (i - '0');
      }
    }
    return result;
  }

  std::string VersionListTraits<char>::toString(std::vector<char> const &vec)
  {
    std::string result;
    for (char const val : vec)
    {
      (result += val) += ".";
    }
    result.pop_back();
    return result;
  }

  std::istream &VersionListTraits<char>::read(std::istream &is, std::vector<char> &vec)
  {
    for (char val = 0; is >> val;)
    {
      vec.push_back(val);

      if (is.get() != '.')
      {
        break;
      }
    }
    return is;
  }

  std::ostream &VersionListTraits<char>::print(std::ostream &os, std::vector<char> const &vec)
  {
    os << toString(vec);
    return os;
  }

  bool VersionListTraits<char>::equal(std::vector<char> const &lhs, std::vector<char> const &rhs)
  {
    return lhs == rhs;
  }

  bool VersionListTraits<char>::less(std::vector<char> const &lhs, std::vector<char> const &rhs)
  {
    return toString(lhs) < toString(rhs);
  }

}  // namespace utils