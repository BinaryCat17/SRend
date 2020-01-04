#pragma once
#include <cassert>
#include <memory>
#include <type_traits>

#if defined _MSC_VER && _MSC_VER < 1900  // MS Visual Studio before VS2015
#define SPIMPL_NO_CPP11_NOEXCEPT
#define SPIMPL_NO_CPP11_CONSTEXPR
#define SPIMPL_NO_CPP11_DEFAULT_MOVE_SPEC_FUNC
#endif

#if !defined SPIMPL_NO_CPP11_NOEXCEPT
#define SPIMPL_NOEXCEPT noexcept
#else
#define SPIMPL_NOEXCEPT
#endif

#if !defined SPIMPL_NO_CPP11_CONSTEXPR
#define SPIMPL_CONSTEXPR constexpr
#else
#define SPIMPL_CONSTEXPR
#endif

namespace utils
{
  namespace details
  {
    template <class T>
    T *defaultCopy(T *src)
    {
      static_assert(sizeof(T) > 0, "defaultCopy cannot copy incomplete Type");
      static_assert(!std::is_void<T>::value, "defaultCopy cannot copy incomplete Type");
      return new T(*src);
    }

    template <class T>
    void defaultDelete(T *p) SPIMPL_NOEXCEPT
    {
      static_assert(sizeof(T) > 0, "defaultDelete cannot delete incomplete Type");
      static_assert(!std::is_void<T>::value, "defaultDelete cannot delete incomplete Type");
      delete p;
    }

    template <class T>
    struct DefaultDeleter
    {
      using Type = void (*)(T *);
    };

    template <class T>
    using DefaultDeleterT = typename DefaultDeleter<T>::Type;

    template <class T>
    struct DefaultCopier
    {
      using Type = T *(*)(T *);
    };

    template <class T>
    using DefaultCopierT = typename DefaultCopier<T>::Type;

    template <class T, class D, class C = details::DefaultCopierT<T>>
    struct IsDefaultManageable : public std::integral_constant<bool, std::is_same<D, DefaultDeleterT<T>>::value &&
                                                                         std::is_same<C, DefaultCopierT<T>>::value>
    {
    };
  }  // namespace details

  template <class T, class Deleter = details::DefaultDeleterT<T>>
  class UniqueImplPtr
  {
   protected:
    static_assert(!std::is_array<T>::value, "UniqueImplPtr specialization for arrays is not implemented");
    struct DummyT
    {
      int dummy__;
    };

   public:
    using Pointer = T *;
    using ConstPointer = typename std::add_const<T>::type *;
    using Reference = T &;
    using ConstReference = typename std::add_const<T>::type &;
    using ElementType = T;
    using DeleterType = typename std::decay<Deleter>::type;
    using UniquePtrType = std::unique_ptr<T, DeleterType>;
    using IsDefaultManageable = details::IsDefaultManageable<T, DeleterType>;

    SPIMPL_CONSTEXPR UniqueImplPtr() SPIMPL_NOEXCEPT : ptr_(nullptr, DeleterType{})
    {
    }

    SPIMPL_CONSTEXPR UniqueImplPtr(std::nullptr_t) SPIMPL_NOEXCEPT : UniqueImplPtr()
    {
    }

    template <class D>
    UniqueImplPtr(Pointer p, D &&d,
        typename std::enable_if<std::is_convertible<D, DeleterType>::value, DummyT>::type = DummyT()) SPIMPL_NOEXCEPT
        : ptr_(std::move(p), std::forward<D>(d))
    {
    }

    template <class U>
    UniqueImplPtr(U *u,
        typename std::enable_if<std::is_convertible<U *, Pointer>::value && IsDefaultManageable::value, DummyT>::type =
            DummyT()) SPIMPL_NOEXCEPT : UniqueImplPtr(u, &details::defaultDelete<T>, &details::defaultCopy<T>)
    {
    }

#ifndef SPIMPL_NO_CPP11_DEFAULT_MOVE_SPEC_FUNC

    UniqueImplPtr(UniqueImplPtr &&r) SPIMPL_NOEXCEPT = default;

#else
    UniqueImplPtr(UniqueImplPtr &&r) SPIMPL_NOEXCEPT : ptr_(std::move(r.ptr_))
    {
    }
#endif

#ifdef SPIMPL_HAS_AUTO_PTR
    template <class U>
    UniqueImplPtr(std::auto_ptr<U> &&u,
        typename std::enable_if<std::is_convertible<U *, Pointer>::value && IsDefaultManageable::value, DummyT>::Type =
            DummyT()) SPIMPL_NOEXCEPT : ptr_(u.release(), &details::default_delete<T>)
    {
    }
#endif

    template <class U>
    UniqueImplPtr(std::unique_ptr<U> &&u,
        typename std::enable_if<std::is_convertible<U *, Pointer>::value && IsDefaultManageable::value, DummyT>::type =
            DummyT()) SPIMPL_NOEXCEPT : ptr_(u.release(), &details::defaultDelete<T>)
    {
    }

    template <class U, class D>
    UniqueImplPtr(std::unique_ptr<U, D> &&u,
        typename std::enable_if<std::is_convertible<U *, Pointer>::value && std::is_convertible<D, DeleterType>::value,
            DummyT>::type = DummyT()) SPIMPL_NOEXCEPT : ptr_(std::move(u))
    {
    }

    template <class U, class D>
    UniqueImplPtr(UniqueImplPtr<U, D> &&u,
        typename std::enable_if<std::is_convertible<U *, Pointer>::value && std::is_convertible<D, DeleterType>::value,
            DummyT>::type = DummyT()) SPIMPL_NOEXCEPT : ptr_(std::move(u.ptr_))
    {
    }

    UniqueImplPtr(const UniqueImplPtr<T, Deleter> &) = delete;

#ifndef SPIMPL_NO_CPP11_DEFAULT_MOVE_SPEC_FUNC

    UniqueImplPtr &operator=(UniqueImplPtr &&r) SPIMPL_NOEXCEPT = default;

#else
    UniqueImplPtr &operator=(UniqueImplPtr &&r) SPIMPL_NOEXCEPT
    {
      ptr_ = std::move(r.ptr_);
      return *this;
    }
#endif

#ifdef SPIMPL_HAS_AUTO_PTR
    template <class U>
    typename std::enable_if<std::is_convertible<U *, Pointer>::value && IsDefaultManageable::value,
        UniqueImplPtr &>::Type
    operator=(std::auto_ptr<U> &&u) SPIMPL_NOEXCEPT
    {
      return operator=(UniqueImplPtr(std::move(u)));
    }
#endif

    template <class U>
    typename std::enable_if<std::is_convertible<U *, Pointer>::value && IsDefaultManageable::value,
        UniqueImplPtr &>::type
    operator=(std::unique_ptr<U> &&u) SPIMPL_NOEXCEPT
    {
      return operator=(UniqueImplPtr(std::move(u)));
    }

    Reference operator=(const UniqueImplPtr<T, Deleter> &) = delete;

    Reference operator*()
    {
      return *ptr_;
    }

    ConstReference operator*() const
    {
      return *ptr_;
    }

    Pointer operator->() SPIMPL_NOEXCEPT
    {
      return get();
    }

    ConstPointer operator->() const SPIMPL_NOEXCEPT
    {
      return get();
    }

    Pointer get() SPIMPL_NOEXCEPT
    {
      return ptr_.get();
    }

    ConstPointer get() const SPIMPL_NOEXCEPT
    {
      return ptr_.get();
    }

    void swap(UniqueImplPtr &u) SPIMPL_NOEXCEPT
    {
      using std::swap;
      ptr_.swap(u.ptr_);
    }

    Pointer release() SPIMPL_NOEXCEPT
    {
      return ptr_.release();
    }

    UniquePtrType releaseUnique() SPIMPL_NOEXCEPT
    {
      return std::move(ptr_);
    }

    explicit operator bool() const SPIMPL_NOEXCEPT
    {
      return static_cast<bool>(ptr_);
    }

    typename std::remove_reference<DeleterType>::type &getDeleter() SPIMPL_NOEXCEPT
    {
      return ptr_.get_deleter();
    }

    const typename std::remove_reference<DeleterType>::type &getDeleter() const SPIMPL_NOEXCEPT
    {
      return ptr_.get_deleter();
    }

   protected:
    UniquePtrType ptr_;
  };

  template <class T, class D>
  inline void swap(UniqueImplPtr<T, D> &l, UniqueImplPtr<T, D> &r) SPIMPL_NOEXCEPT
  {
    l.swap(r);
  }

  template <class T1, class D1, class T2, class D2>
  inline bool operator==(const UniqueImplPtr<T1, D1> &l, const UniqueImplPtr<T2, D2> &r)
  {
    return l.get() == r.get();
  }

  template <class T1, class D1, class T2, class D2>
  inline bool operator!=(const UniqueImplPtr<T1, D1> &l, const UniqueImplPtr<T2, D2> &r)
  {
    return !(l == r);
  }

  template <class T1, class D1, class T2, class D2>
  inline bool operator<(const UniqueImplPtr<T1, D1> &l, const UniqueImplPtr<T2, D2> &r)
  {
    using P1 = typename UniqueImplPtr<T1, D1>::Pointer;
    using P2 = typename UniqueImplPtr<T2, D2>::Pointer;
    using Ct = typename std::common_type<P1, P2>::type;
    return std::less<Ct>()(l.get(), r.get());
  }

  template <class T1, class D1, class T2, class D2>
  inline bool operator>(const UniqueImplPtr<T1, D1> &l, const UniqueImplPtr<T2, D2> &r)
  {
    return r < l;
  }

  template <class T1, class D1, class T2, class D2>
  inline bool operator<=(const UniqueImplPtr<T1, D1> &l, const UniqueImplPtr<T2, D2> &r)
  {
    return !(r < l);
  }

  template <class T1, class D1, class T2, class D2>
  inline bool operator>=(const UniqueImplPtr<T1, D1> &l, const UniqueImplPtr<T2, D2> &r)
  {
    return !(l < r);
  }

  template <class T, class D>
  inline bool operator==(const UniqueImplPtr<T, D> &p, std::nullptr_t) SPIMPL_NOEXCEPT
  {
    return !p;
  }

  template <class T, class D>
  inline bool operator==(std::nullptr_t, const UniqueImplPtr<T, D> &p) SPIMPL_NOEXCEPT
  {
    return !p;
  }

  template <class T, class D>
  inline bool operator!=(const UniqueImplPtr<T, D> &p, std::nullptr_t) SPIMPL_NOEXCEPT
  {
    return static_cast<bool>(p);
  }

  template <class T, class D>
  inline bool operator!=(std::nullptr_t, const UniqueImplPtr<T, D> &p) SPIMPL_NOEXCEPT
  {
    return static_cast<bool>(p);
  }

  template <class T, class D>
  inline bool operator<(const UniqueImplPtr<T, D> &l, std::nullptr_t)
  {
    using P = typename UniqueImplPtr<T, D>::Pointer;
    return std::less<P>()(l.get(), nullptr);
  }

  template <class T, class D>
  inline bool operator<(std::nullptr_t, const UniqueImplPtr<T, D> &p)
  {
    using P = typename UniqueImplPtr<T, D>::Pointer;
    return std::less<P>()(nullptr, p.get());
  }

  template <class T, class D>
  inline bool operator>(const UniqueImplPtr<T, D> &p, std::nullptr_t)
  {
    return nullptr < p;
  }

  template <class T, class D>
  inline bool operator>(std::nullptr_t, const UniqueImplPtr<T, D> &p)
  {
    return p < nullptr;
  }

  template <class T, class D>
  inline bool operator<=(const UniqueImplPtr<T, D> &p, std::nullptr_t)
  {
    return !(nullptr < p);
  }

  template <class T, class D>
  inline bool operator<=(std::nullptr_t, const UniqueImplPtr<T, D> &p)
  {
    return !(p < nullptr);
  }

  template <class T, class D>
  inline bool operator>=(const UniqueImplPtr<T, D> &p, std::nullptr_t)
  {
    return !(p < nullptr);
  }

  template <class T, class D>
  inline bool operator>=(std::nullptr_t, const UniqueImplPtr<T, D> &p)
  {
    return !(nullptr < p);
  }

  template <class T, class... Args>
  inline UniqueImplPtr<T> makeUniqueImpl(Args &&... args)
  {
    return UniqueImplPtr<T>(new T(std::forward<Args>(args)...), &details::defaultDelete<T>);
  }

  // Helpers to manage unique impl, stored in std::unique_ptr
  template <class T, class Deleter = details::DefaultDeleterT<T>, class Copier = details::DefaultCopierT<T>>
  class ImplPtr : public UniqueImplPtr<T, Deleter>
  {
    using BaseType = UniqueImplPtr<T, Deleter>;
    using DummyT = typename BaseType::DummyT;

   public:
    using Pointer = typename BaseType::Pointer;
    using ConstPointer = typename BaseType::ConstPointer;
    using Reference = typename BaseType::Reference;
    using ConstReference = typename BaseType::ConstReference;
    using ElementType = typename BaseType::ElementType;
    using DeleterType = typename BaseType::DeleterType;
    using UniquePtrType = typename BaseType::UniquePtrType;
    using CopierType = typename std::decay<Copier>::type;
    using IsDefaultManageable = details::IsDefaultManageable<T, DeleterType, CopierType>;

    SPIMPL_CONSTEXPR ImplPtr() SPIMPL_NOEXCEPT : BaseType(nullptr, DeleterType{}), copier_(CopierType{})
    {
    }

    SPIMPL_CONSTEXPR ImplPtr(std::nullptr_t) SPIMPL_NOEXCEPT : ImplPtr()
    {
    }

    template <class D, class C>
    ImplPtr(Pointer p, D &&d, C &&c,
        typename std::enable_if<std::is_convertible<D, DeleterType>::value && std::is_convertible<C, CopierType>::value,
            typename BaseType::DummyT>::type = typename BaseType::DummyT()) SPIMPL_NOEXCEPT
        : BaseType(std::move(p), std::forward<D>(d)),
          copier_(std::forward<C>(c))
    {
    }

    template <class U>
    ImplPtr(U *u,
        typename std::enable_if<std::is_convertible<U *, Pointer>::value && IsDefaultManageable::value, DummyT>::type =
            DummyT()) SPIMPL_NOEXCEPT : ImplPtr(u, &details::defaultDelete<T>, &details::defaultCopy<T>)
    {
    }

    ImplPtr(const ImplPtr &r) : ImplPtr(r.clone())
    {
    }

#ifndef SPIMPL_NO_CPP11_DEFAULT_MOVE_SPEC_FUNC

    ImplPtr(ImplPtr &&r) SPIMPL_NOEXCEPT = default;

#else
    ImplPtr(ImplPtr &&r) SPIMPL_NOEXCEPT : BaseType(std::move(r.ptr_)), copier_(std::move(r.copier_))
    {
    }
#endif

#ifdef SPIMPL_HAS_AUTO_PTR
    template <class U>
    ImplPtr(std::auto_ptr<U> &&u,
        typename std::enable_if<std::is_convertible<U *, Pointer>::value && IsDefaultManageable::value, DummyT>::Type =
            DummyT()) SPIMPL_NOEXCEPT : BaseType(u.release(), &details::default_delete<T>),
                                        copier_(&details::default_copy<T>)
    {
    }
#endif

    template <class U>
    ImplPtr(std::unique_ptr<U> &&u,
        typename std::enable_if<std::is_convertible<U *, Pointer>::value && IsDefaultManageable::value, DummyT>::type =
            DummyT()) SPIMPL_NOEXCEPT : BaseType(u.release(), &details::defaultDelete<T>)
    {
    }

    template <class U, class D, class C>
    ImplPtr(std::unique_ptr<U, D> &&u, C &&c,
        typename std::enable_if<std::is_convertible<U *, Pointer>::value && std::is_convertible<D, DeleterType>::value,
            DummyT>::type = DummyT()) SPIMPL_NOEXCEPT : BaseType(std::move(u)),
                                                        copier_(std::forward<C>(c))
    {
    }

    template <class U, class D, class C>
    ImplPtr(ImplPtr<U, D, C> &&u,
        typename std::enable_if<std::is_convertible<U *, Pointer>::value && std::is_convertible<D, DeleterType>::value,
            DummyT>::type = DummyT()) SPIMPL_NOEXCEPT : BaseType(std::move(u.ptr_)),
                                                        copier_(std::move(u.copier_))
    {
    }

    ImplPtr &operator=(const ImplPtr &r)
    {
      if (this == &r) return *this;

      return operator=(r.clone());
    }

#ifndef SPIMPL_NO_CPP11_DEFAULT_MOVE_SPEC_FUNC

    ImplPtr &operator=(ImplPtr &&r) SPIMPL_NOEXCEPT = default;

#else
    ImplPtr &operator=(ImplPtr &&r) SPIMPL_NOEXCEPT
    {
      BaseType::ptr_ = std::move(r.ptr_);
      copier_ = std::move(r.copier_);
      return *this;
    }
#endif

    template <class U, class D, class C>
    typename std::enable_if<std::is_convertible<U *, Pointer>::value && std::is_convertible<D, DeleterType>::value &&
                                std::is_convertible<C, CopierType>::value,
        ImplPtr &>::type
    operator=(const ImplPtr<U, D, C> &u)
    {
      return operator=(u.clone());
    }

    //

#ifdef SPIMPL_HAS_AUTO_PTR
    template <class U>
    typename std::enable_if<std::is_convertible<U *, Pointer>::value && IsDefaultManageable::value, ImplPtr &>::Type
    operator=(std::auto_ptr<U> &&u) SPIMPL_NOEXCEPT
    {
      return operator=(ImplPtr(std::move(u)));
    }
#endif

    template <class U>
    typename std::enable_if<std::is_convertible<U *, Pointer>::value && IsDefaultManageable::value, ImplPtr &>::type
    operator=(std::unique_ptr<U> &&u) SPIMPL_NOEXCEPT
    {
      return operator=(ImplPtr(std::move(u)));
    }

    template <class U, class D, class C>
    typename std::enable_if<std::is_convertible<U *, Pointer>::value && std::is_convertible<D, DeleterType>::value &&
                                std::is_convertible<C, CopierType>::value,
        ImplPtr &>::type
    operator=(ImplPtr<U, D, C> &&u) SPIMPL_NOEXCEPT
    {
      BaseType::ptr_ = std::move(u.ptr_);
      copier_ = std::move(u.copier_);
      return *this;
    }

    void swap(ImplPtr &u) SPIMPL_NOEXCEPT
    {
      using std::swap;
      BaseType::ptr_.swap(u.ptr_);
      swap(copier_, u.copier_);
    }

    ImplPtr clone() const
    {
      return ImplPtr(BaseType::ptr_ ? copier_(BaseType::ptr_.get()) : nullptr, BaseType::ptr_.get_deleter(), copier_);
    }

    const typename std::remove_reference<CopierType>::type &getCopier() const SPIMPL_NOEXCEPT
    {
      return copier_;
    }

    typename std::remove_reference<CopierType>::type &getCopier() SPIMPL_NOEXCEPT
    {
      return copier_;
    }

   private:
    CopierType copier_;
  };

  template <class T, class... Args>
  inline ImplPtr<T> makeImpl(Args &&... args)
  {
    return ImplPtr<T>(new T(std::forward<Args>(args)...), &details::defaultDelete<T>, &details::defaultCopy<T>);
  }

  template <class T, class D, class C>
  inline void swap(ImplPtr<T, D, C> &l, ImplPtr<T, D, C> &r) SPIMPL_NOEXCEPT
  {
    l.swap(r);
  }
}  // namespace utils

namespace std
{
  template <class T, class D>
  struct hash<utils::UniqueImplPtr<T, D>>
  {
    using argument_type = utils::UniqueImplPtr<T, D>;
    using result_type = size_t;

    result_type operator()(const argument_type &p) const SPIMPL_NOEXCEPT
    {
      return hash<typename argument_type::Pointer>()(p.get());
    }
  };

  template <class T, class D, class C>
  struct hash<utils::ImplPtr<T, D, C>>
  {
    using argument_type = utils::ImplPtr<T, D, C>;
    using result_type = size_t;

    result_type operator()(const argument_type &p) const SPIMPL_NOEXCEPT
    {
      return hash<typename argument_type::Pointer>()(p.get());
    }
  };
}  // namespace std
