#pragma once
#include <iosfwd>
#include <string>
#include <vector>

namespace utils
{
  // Version ----------------------------------------------------------------------------------------------------------

  class Version
  {
    friend std::istream &operator>>(std::istream &is, Version &rhs);

    friend std::ostream &operator<<(std::ostream &os, Version const &rhs);

   public:
    virtual ~Version() = default;

    [[nodiscard]] virtual unsigned toUint() const = 0;

    [[nodiscard]] virtual std::string toString() const = 0;

   private:
    virtual std::istream &read(std::istream &is) = 0;

    virtual std::ostream &print(std::ostream &os) const = 0;
  };

  inline std::istream &operator>>(std::istream &is, Version &rhs)
  {
    return rhs.read(is);
  }

  inline std::ostream &operator<<(std::ostream &os, Version const &rhs)
  {
    return rhs.print(os);
  }

  // VersionListTraits ------------------------------------------------------------------------------------------------

  template <typename>
  struct VersionListTraits;

  template <>
  struct VersionListTraits<unsigned>
  {
    static unsigned toUint(std::vector<unsigned> const &vec);

    static std::string toString(std::vector<unsigned> const &vec);

    static std::istream &read(std::istream &is, std::vector<unsigned> &vec);

    static std::ostream &print(std::ostream &os, std::vector<unsigned> const &vec);

    static bool equal(std::vector<unsigned> const &lhs, std::vector<unsigned> const &rhs);

    static bool less(std::vector<unsigned> const &lhs, std::vector<unsigned> const &rhs);
  };

  template <>
  struct VersionListTraits<char>
  {
    static unsigned toUint(std::vector<char> const &vec);

    static std::string toString(std::vector<char> const &vec);

    static std::istream &read(std::istream &is, std::vector<char> &vec);

    static std::ostream &print(std::ostream &os, std::vector<char> const &vec);

    static bool equal(std::vector<char> const &lhs, std::vector<char> const &rhs);

    static bool less(std::vector<char> const &lhs, std::vector<char> const &rhs);
  };

  // VersionList ------------------------------------------------------------------------------------------------------

  template <typename T, typename Traits = VersionListTraits<T>>
  class BasicVersionList : public Version
  {
   public:
    BasicVersionList() = default;

    BasicVersionList(std::initializer_list<T> il)
        : vec_(il.begin(), il.end()), str_(Traits::toUint(vec_)), uint_(Traits::toString(vec_))
    {
    }

    [[nodiscard]] unsigned int toUint() const override
    {
      return uint_;
    }

    [[nodiscard]] std::string toString() const override
    {
      return str_;
    }

   private:
    std::istream &read(std::istream &is) override
    {
      return Traits::read(is, vec_);
    }

    std::ostream &print(std::ostream &os) const override
    {
      return Traits::print(os, vec_);
    }

   private:
    std::vector<T> vec_;
    std::string str_;
    unsigned uint_ = 0;
  };

  using VersionList = BasicVersionList<unsigned>;
  using VersionListChar = BasicVersionList<char>;

}  // namespace utils