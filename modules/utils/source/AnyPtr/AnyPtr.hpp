#pragma once
#include <any>
#include <memory>

namespace utils
{
  // UniqueAnyPtr -----------------------------------------------------------------------------------------------------

  class UniqueAnyPtr
  {
   public:
    template <typename T>
    explicit UniqueAnyPtr(T const &val) : val_(val), size_(sizeof(T)), p_val_(&std::any_cast<T const &>(val_))
    {
    }

    UniqueAnyPtr(UniqueAnyPtr const &rhs) = delete;

    UniqueAnyPtr &operator=(UniqueAnyPtr const &rhs) = delete;

    UniqueAnyPtr(UniqueAnyPtr &&rhs) = default;

    UniqueAnyPtr &operator=(UniqueAnyPtr &&rhs) = default;

    [[nodiscard]] size_t size() const noexcept
    {
      return size_;
    }

    [[nodiscard]] void const *data() const noexcept
    {
      return p_val_;
    }

   private:
    std::any val_;
    size_t size_;
    void const *p_val_;
  };

  bool operator==(UniqueAnyPtr const &lhs, UniqueAnyPtr const &rhs);

  bool operator!=(UniqueAnyPtr const &lhs, UniqueAnyPtr const &rhs);

  // SharedAnyPtr -----------------------------------------------------------------------------------------------------

  class SharedAnyPtr
  {
   public:
    template <typename T>
    explicit SharedAnyPtr(T const &val) : ptr_(std::make_shared<UniqueAnyPtr>(val))
    {
    }

    [[nodiscard]] size_t size() const noexcept
    {
      return ptr_->size();
    }

    [[nodiscard]] void const *data() const noexcept
    {
      return ptr_->data();
    }

   private:
    std::shared_ptr<UniqueAnyPtr> ptr_;
  };

  bool operator==(SharedAnyPtr const &lhs, SharedAnyPtr const &rhs);

  bool operator!=(SharedAnyPtr const &lhs, SharedAnyPtr const &rhs);

}  // namespace utils