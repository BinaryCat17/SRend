#include "AnyPtr.hpp"

namespace utils
{
  // UniqueAnyPtr -----------------------------------------------------------------------------------------------------

  bool operator==(UniqueAnyPtr const &lhs, UniqueAnyPtr const &rhs)
  {
    return lhs.data() == rhs.data();
  }

  bool operator!=(UniqueAnyPtr const &lhs, UniqueAnyPtr const &rhs)
  {
    return !(lhs == rhs);
  }

  // SharedAnyPtr -----------------------------------------------------------------------------------------------------

  bool operator==(SharedAnyPtr const &lhs, SharedAnyPtr const &rhs)
  {
    return lhs.data() == rhs.data();
  }

  bool operator!=(SharedAnyPtr const &lhs, SharedAnyPtr const &rhs)
  {
    return !(lhs == rhs);
  }
}  // namespace utils