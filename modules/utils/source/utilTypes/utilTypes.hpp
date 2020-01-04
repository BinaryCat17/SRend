#pragma once
#include <iosfwd>

namespace utils
{
  // Extent -----------------------------------------------------------------------------------------------------------

  template <typename T>
  class BasicExtent2D
  {
   public:
    BasicExtent2D() = default;

    explicit BasicExtent2D(T width, T height) : width_(width), height_(height)
    {
    }

    T width() const
    {
      return width_;
    }

    T height() const
    {
      return height_;
    }

    void setWidth(T val)
    {
      width_ = val;
    }

    void setHeight(T val)
    {
      height_ = val;
    }

   private:
    T width_ = {};
    T height_ = {};
  };

  template <typename T1, typename T2>
  bool operator==(BasicExtent2D<T1> const &lhs, BasicExtent2D<T2> const &rhs)
  {
    return lhs.width() == rhs.width() && lhs.height() == rhs.height();
  }

  template <typename T1, typename T2>
  bool operator!=(BasicExtent2D<T1> const &lhs, BasicExtent2D<T2> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T1, typename T2>
  bool operator<(BasicExtent2D<T1> const &lhs, BasicExtent2D<T2> const &rhs)
  {
    if (lhs.width() < rhs.width_) return true;
    if (rhs.width() < lhs.width()) return false;
    return lhs.height() < rhs.height();
  }

  template <typename T1, typename T2>
  bool operator>(BasicExtent2D<T1> const &lhs, BasicExtent2D<T2> const &rhs)
  {
    return rhs < lhs;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicExtent2D<T1> const &lhs, BasicExtent2D<T2> const &rhs)
  {
    return !(rhs < lhs);
  }

  template <typename T1, typename T2>
  bool operator>=(BasicExtent2D<T1> const &lhs, BasicExtent2D<T2> const &rhs)
  {
    return !(lhs < rhs);
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &os, BasicExtent2D<T> const &rhs)
  {
    os << rhs.width() << " " << rhs.height();
    return os;
  }

  template <typename T>
  std::istream &operator>>(std::istream &is, BasicExtent2D<T> &rhs)
  {
    T x, y;
    is >> x >> y;
    rhs.setWidth(x);
    rhs.setHeight(y);
    return is;
  }

  template <typename T>
  class BasicExtent3D
  {
   public:
    BasicExtent3D() = default;

    explicit BasicExtent3D(T width, T height, T depth) : width_(width), height_(height), depth_(depth)
    {
    }

    explicit operator BasicExtent2D<T>()
    {
      return BasicExtent2D<T>(width(), height());
    }

    T width() const
    {
      return width_;
    }

    T height() const
    {
      return height_;
    }

    T depth() const
    {
      return depth_;
    }

    void setWidth(T val)
    {
      width_ = val;
    }

    void setHeight(T val)
    {
      height_ = val;
    }

    void setDepth(T val)
    {
      depth_ = val;
    }

   private:
    T width_ = {};
    T height_ = {};
    T depth_ = {};
  };

  template <typename T1, typename T2>
  bool operator==(BasicExtent3D<T1> const &lhs, BasicExtent3D<T2> const &rhs)
  {
    return lhs.width() == rhs.width() && lhs.height() == rhs.height() && lhs.depth() == rhs.depth();
  }

  template <typename T1, typename T2>
  bool operator!=(BasicExtent3D<T1> const &lhs, BasicExtent3D<T2> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T1, typename T2>
  bool operator<(BasicExtent3D<T1> const &lhs, BasicExtent3D<T2> const &rhs)
  {
    if (lhs.width() < rhs.width()) return true;
    if (rhs.width() < lhs.width()) return false;
    if (lhs.height() < rhs.height()) return true;
    if (rhs.height() < lhs.height()) return false;
    return lhs.depth() < rhs.depth();
  }

  template <typename T1, typename T2>
  bool operator>(BasicExtent3D<T1> const &lhs, BasicExtent3D<T2> const &rhs)
  {
    return rhs < lhs;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicExtent3D<T1> const &lhs, BasicExtent3D<T2> const &rhs)
  {
    return !(rhs < lhs);
  }

  template <typename T1, typename T2>
  bool operator>=(BasicExtent3D<T1> const &lhs, BasicExtent3D<T2> const &rhs)
  {
    return !(lhs < rhs);
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &os, BasicExtent3D<T> const &rhs)
  {
    os << rhs.width() << " " << rhs.height() << " " << rhs.depth();
    return os;
  }

  template <typename T>
  std::istream &operator>>(std::istream &is, BasicExtent3D<T> &rhs)
  {
    T x, y, z;
    is >> x >> y >> z;
    rhs.setWidth(x);
    rhs.setHeight(y);
    rhs.setDepth(z);
    return is;
  }

  // Position ---------------------------------------------------------------------------------------------------------

  template <typename T>
  class BasicPosition2D
  {
    template <typename T1, typename T2>
    friend bool operator==(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs);

    template <typename T1>
    friend std::ostream &operator<<(std::ostream &os, BasicPosition2D<T1> const &rhs);

    template <typename T1>
    friend std::istream &operator>>(std::istream &is, BasicPosition2D<T1> &rhs);

    template <typename T1, typename T2>
    friend bool operator<(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator<=(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>=(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs);

   public:
    BasicPosition2D() = default;

    explicit BasicPosition2D(T x, T y) : base_(x, y)
    {
    }

    T x() const
    {
      return base_.width();
    }

    T y() const
    {
      return base_.height();
    }

    void setX(T val)
    {
      base_.setWidth(val);
    }

    void setY(T val)
    {
      base_.setHeight(val);
    }

   private:
    BasicExtent2D<T> base_;
  };

  template <typename T1, typename T2>
  bool operator==(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs)
  {
    return lhs.base_ == rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator!=(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T1>
  std::ostream &operator<<(std::ostream &os, BasicPosition2D<T1> const &rhs)
  {
    return os << rhs.base_;
  }

  template <typename T1>
  std::istream &operator>>(std::istream &is, BasicPosition2D<T1> &rhs)
  {
    return is >> rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs)
  {
    return lhs.base_ < rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs)
  {
    return lhs.base_ > rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs)
  {
    return lhs.base_ <= rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>=(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs)
  {
    return lhs.base_ >= rhs.base_;
  }

  template <typename T>
  class BasicPosition3D
  {
    template <typename T1, typename T2>
    friend bool operator==(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs);

    template <typename T1>
    friend std::ostream &operator<<(std::ostream &os, BasicPosition3D<T1> const &rhs);

    template <typename T1>
    friend std::istream &operator>>(std::istream &is, BasicPosition3D<T1> &rhs);

    template <typename T1, typename T2>
    friend bool operator<(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator<=(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>=(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs);

   public:
    BasicPosition3D() = default;

    explicit BasicPosition3D(T x, T y, T z) : base_(x, y, z)
    {
    }

    explicit operator BasicExtent2D<T>()
    {
      return BasicExtent2D<T>(x(), y());
    }

    T x() const
    {
      return base_.width();
    }

    T y() const
    {
      return base_.height();
    }

    T z() const
    {
      return base_.depth();
    }

    void setX(T val)
    {
      base_.setWidth(val);
    }

    void setY(T val)
    {
      base_.setHeight(val);
    }

    void setZ(T val)
    {
      base_.setDepth(val);
    }

   private:
    BasicExtent3D<T> base_;
  };

  template <typename T>
  bool operator==(BasicPosition3D<T> const &lhs, BasicPosition3D<T> const &rhs)
  {
    return lhs.base_ == rhs.base_;
  }

  template <typename T>
  bool operator!=(BasicPosition3D<T> const &lhs, BasicPosition3D<T> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &os, BasicPosition3D<T> const &rhs)
  {
    return os << rhs.base_;
  }

  template <typename T1>
  std::istream &operator>>(std::istream &is, BasicPosition3D<T1> &rhs)
  {
    return is >> rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs)
  {
    return lhs.base_ < rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs)
  {
    return lhs.base_ > rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs)
  {
    return lhs.base_ <= rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>=(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs)
  {
    return lhs.base_ >= rhs.base_;
  }

  // Offset -----------------------------------------------------------------------------------------------------------

  template <typename T>
  class BasicOffset2D
  {
    template <typename T1, typename T2>
    friend bool operator==(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs);

    template <typename T1>
    friend std::ostream &operator<<(std::ostream &os, BasicOffset2D<T1> const &rhs);

    template <typename T1>
    friend std::istream &operator>>(std::istream &is, BasicOffset2D<T1> &rhs);

    template <typename T1, typename T2>
    friend bool operator<(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator<=(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>=(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs);

   public:
    BasicOffset2D() = default;

    explicit BasicOffset2D(T x, T y) : base_(x, y)
    {
    }

    T x() const
    {
      return base_.width();
    }

    T y() const
    {
      return base_.height();
    }

    void setX(T val)
    {
      base_.setWidth(val);
    }

    void setY(T val)
    {
      base_.setHeight(val);
    }

   private:
    BasicExtent2D<T> base_;
  };

  template <typename T1, typename T2>
  bool operator==(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs)
  {
    return lhs.base_ == rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator!=(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T1>
  std::ostream &operator<<(std::ostream &os, BasicOffset2D<T1> const &rhs)
  {
    return os << rhs.base_;
  }

  template <typename T1>
  std::istream &operator>>(std::istream &is, BasicOffset2D<T1> &rhs)
  {
    return is >> rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs)
  {
    return lhs.base_ < rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs)
  {
    return lhs.base_ > rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs)
  {
    return lhs.base_ <= rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>=(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs)
  {
    return lhs.base_ >= rhs.base_;
  }

  template <typename T>
  class BasicOffset3D
  {
    template <typename T1, typename T2>
    friend bool operator==(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs);

    template <typename T1>
    friend std::ostream &operator<<(std::ostream &os, BasicOffset3D<T1> const &rhs);

    template <typename T1>
    friend std::istream &operator>>(std::istream &is, BasicOffset3D<T1> &rhs);

    template <typename T1, typename T2>
    friend bool operator<(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator<=(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>=(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs);

   public:
    BasicOffset3D() = default;

    explicit BasicOffset3D(T x, T y, T z) : base_(x, y, z)
    {
    }

    explicit operator BasicExtent2D<T>()
    {
      return BasicExtent2D<T>(x(), y());
    }

    T x() const
    {
      return base_.width();
    }

    T y() const
    {
      return base_.height();
    }

    T z() const
    {
      return base_.depth();
    }

    void setX(T val)
    {
      base_.setWidth(val);
    }

    void setY(T val)
    {
      base_.setHeight(val);
    }

    void setZ(T val)
    {
      base_.setDepth(val);
    }

   private:
    BasicExtent3D<T> base_;
  };

  template <typename T>
  bool operator==(BasicOffset3D<T> const &lhs, BasicOffset3D<T> const &rhs)
  {
    return lhs.base_ == rhs.base_;
  }

  template <typename T>
  bool operator!=(BasicOffset3D<T> const &lhs, BasicOffset3D<T> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &os, BasicOffset3D<T> const &rhs)
  {
    return os << rhs.base_;
  }

  template <typename T1>
  std::istream &operator>>(std::istream &is, BasicOffset3D<T1> &rhs)
  {
    return is >> rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs)
  {
    return lhs.base_ < rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs)
  {
    return lhs.base_ > rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs)
  {
    return lhs.base_ <= rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>=(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs)
  {
    return lhs.base_ >= rhs.base_;
  }

  // Rect -------------------------------------------------------------------------------------------------------------

  template <typename T>
  class BasicRect2D
  {
   public:
    BasicRect2D() = default;

    explicit BasicRect2D(T x, T y, T width, T height) : position_(x, y), extent_(width, height)
    {
    }

    T x() const
    {
      return position_.x();
    }

    T y() const
    {
      return position_.y();
    }

    T width() const
    {
      return extent_.width();
    }

    T height() const
    {
      return extent_.height();
    }

    void setX(T val)
    {
      position_.setX(val);
    }

    void setY(T val)
    {
      position_.setY(val);
    }

    void setWidth(T val)
    {
      extent_.setWidth(val);
    }

    void setHeight(T val)
    {
      extent_.setHeight(val);
    }

   private:
    BasicPosition2D<T> position_;
    BasicExtent2D<T> extent_;
  };

  template <typename T1, typename T2>
  bool operator==(BasicRect2D<T1> const &lhs, BasicRect2D<T2> const &rhs)
  {
    return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.width() == rhs.width() && lhs.height() == rhs.height();
  }

  template <typename T1, typename T2>
  bool operator!=(BasicRect2D<T1> const &lhs, BasicRect2D<T2> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T1, typename T2>
  bool operator<(BasicRect2D<T1> const &lhs, BasicRect2D<T2> const &rhs)
  {
    if (lhs.width() < rhs.width()) return true;
    if (rhs.width() < lhs.width()) return false;
    return lhs.height() < rhs.height();
  }

  template <typename T1, typename T2>
  bool operator>(BasicRect2D<T1> const &lhs, BasicRect2D<T2> const &rhs)
  {
    return rhs < lhs;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicRect2D<T1> const &lhs, BasicRect2D<T2> const &rhs)
  {
    return !(rhs < lhs);
  }

  template <typename T1, typename T2>
  bool operator>=(BasicRect2D<T1> const &lhs, BasicRect2D<T2> const &rhs)
  {
    return !(lhs < rhs);
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &os, BasicRect2D<T> const &rhs)
  {
    os << rhs.x() << " " << rhs.y() << " " << rhs.width() << " " << rhs.height();
    return os;
  }

  template <typename T>
  std::istream &operator>>(std::istream &is, BasicRect2D<T> &rhs)
  {
    T x, y, width, height;
    is >> x >> y >> width >> height;
    rhs.setX(x);
    rhs.setY(y);
    rhs.setWidth(width);
    rhs.setHeight(height);
    return is;
  }

  template <typename T>
  class BasicRect3D
  {
   public:
    BasicRect3D() = default;

    explicit BasicRect3D(T x, T y, T z, T width, T height, T depth) : position_(x, y, z), extent_(width, height, depth)
    {
    }

    T x() const
    {
      return position_.x();
    }

    T y() const
    {
      return position_.y();
    }

    T z() const
    {
      return position_.z();
    }

    T width() const
    {
      return extent_.width();
    }

    T height() const
    {
      return extent_.height();
    }

    T depth() const
    {
      return extent_.depth();
    }

    void setX(T val)
    {
      position_.setX(val);
    }

    void setY(T val)
    {
      position_.setY(val);
    }

    void setZ(T val)
    {
      position_.setZ(val);
    }

    void setWidth(T val)
    {
      extent_.setWidth(val);
    }

    void setHeight(T val)
    {
      extent_.setHeight(val);
    }

    void setDepth(T val)
    {
      extent_.setDepth()(val);
    }

   private:
    BasicPosition3D<T> position_;
    BasicExtent3D<T> extent_;
  };

  template <typename T1, typename T2>
  bool operator==(BasicRect3D<T1> const &lhs, BasicRect3D<T2> const &rhs)
  {
    return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z() && lhs.width() == rhs.width() &&
           lhs.height() == rhs.height() && lhs.depth() == rhs.depth();
  }

  template <typename T1, typename T2>
  bool operator!=(BasicRect3D<T1> const &lhs, BasicRect3D<T2> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T1, typename T2>
  bool operator<(BasicRect3D<T1> const &lhs, BasicRect3D<T2> const &rhs)
  {
    if (lhs.width() < rhs.width()) return true;
    if (rhs.width() < lhs.width()) return false;
    if (lhs.height() < rhs.height()) return true;
    if (rhs.height() < lhs.height()) return false;
    return lhs.depth() < rhs.depth();
  }

  template <typename T1, typename T2>
  bool operator>(BasicRect3D<T1> const &lhs, BasicRect3D<T2> const &rhs)
  {
    return rhs < lhs;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicRect3D<T1> const &lhs, BasicRect3D<T2> const &rhs)
  {
    return !(rhs < lhs);
  }

  template <typename T1, typename T2>
  bool operator>=(BasicRect3D<T1> const &lhs, BasicRect3D<T2> const &rhs)
  {
    return !(lhs < rhs);
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &os, BasicRect3D<T> const &rhs)
  {
    os << rhs.x() << " " << rhs.y() << " " << rhs.z() << " " << rhs.width() << " " << rhs.height() << rhs.depth()
       << " ";
    return os;
  }

  template <typename T>
  std::istream &operator>>(std::istream &is, BasicRect3D<T> &rhs)
  {
    T x, y, z, width, height, depth;
    is >> x >> y >> z >> width >> height >> depth;
    rhs.setX(x);
    rhs.setY(y);
    rhs.setZ(z);
    rhs.setWidth(width);
    rhs.setHeight(height);
    rhs.setDepth(depth);
    return is;
  }

  // Viewport ---------------------------------------------------------------------------------------------------------

  template <typename T>
  class BasicViewport
  {
   public:
    BasicViewport() = default;

    explicit BasicViewport(T x, T y, T width, T height, T minDepth, T maxDepth)
        : position_(x, y), extent_(width, height), minDepth_(minDepth), maxDepth_(maxDepth)
    {
    }

    T x() const
    {
      return position_.x();
    }

    T y() const
    {
      return position_.y();
    }

    T width() const
    {
      return extent_.width();
    }

    T height() const
    {
      return extent_.height();
    }

    T minDepth() const
    {
      return minDepth_;
    }

    T maxDepth() const
    {
      return maxDepth_;
    }

    void setX(T val)
    {
      position_.setX(val);
    }

    void setY(T val)
    {
      position_.setY(val);
    }

    void setWidth(T val)
    {
      extent_.setWidth(val);
    }

    void setHeight(T val)
    {
      extent_.setHeight(val);
    }

    void setMinDepth(T val)
    {
      minDepth_ = val;
    }

    void setMaxDepth(T val)
    {
      maxDepth_ = val;
    }

   private:
    BasicPosition2D<T> position_;
    BasicExtent2D<T> extent_;
    T minDepth_;
    T maxDepth_;
  };

  template <typename T1, typename T2>
  bool operator==(BasicViewport<T1> const &lhs, BasicViewport<T2> const &rhs)
  {
    return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.width() == rhs.width() && lhs.height() == rhs.height() &&
           lhs.minDepth() == rhs.minDepth() && lhs.maxDepth() == rhs.maxDepth();
  }

  template <typename T1, typename T2>
  bool operator!=(BasicViewport<T1> const &lhs, BasicViewport<T2> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T1, typename T2>
  bool operator<(BasicViewport<T1> const &lhs, BasicViewport<T2> const &rhs)
  {
    if (lhs.width() < rhs.width()) return true;
    if (rhs.width() < lhs.width()) return false;
    return lhs.height() < rhs.height();
  }

  template <typename T1, typename T2>
  bool operator>(BasicViewport<T1> const &lhs, BasicViewport<T2> const &rhs)
  {
    return rhs < lhs;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicViewport<T1> const &lhs, BasicViewport<T2> const &rhs)
  {
    return !(rhs < lhs);
  }

  template <typename T1, typename T2>
  bool operator>=(BasicViewport<T1> const &lhs, BasicViewport<T2> const &rhs)
  {
    return !(lhs < rhs);
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &os, BasicViewport<T> const &rhs)
  {
    os << rhs.x() << " " << rhs.y() << " " << rhs.width() << " " << rhs.height() << " " << rhs.minDepth() << " "
       << rhs.maxDepth();
    return os;
  }

  template <typename T>
  std::istream &operator>>(std::istream &is, BasicViewport<T> &rhs)
  {
    T x, y, width, height, minDepth, maxDepth;
    is >> x >> y >> width >> height >> minDepth >> maxDepth;
    rhs.setX(x);
    rhs.setY(y);
    rhs.setWidth(width);
    rhs.setHeight(height);
    rhs.setMinDepth(minDepth);
    rhs.setMaxDepth(maxDepth);
    return is;
  }

  // aliases ----------------------------------------------------------------------------------------------------------

  using SizeT = std::size_t;
  using OffsetT = SizeT;
  using AlignmentT = SizeT;
  using IndexT = SizeT;

  using Extent2D = BasicExtent2D<unsigned>;
  using Extent2Df = BasicExtent2D<float>;

  using Extent3D = BasicExtent3D<unsigned>;
  using Extent3Df = BasicExtent3D<float>;

  using Position2D = BasicPosition2D<unsigned>;
  using Position2Df = BasicPosition2D<float>;

  using Position3D = BasicPosition3D<unsigned>;
  using Position3Df = BasicPosition3D<float>;

  using Offset2D = BasicOffset2D<unsigned>;
  using Offset2Df = BasicOffset2D<float>;

  using Offset3D = BasicOffset3D<unsigned>;
  using Offset3Df = BasicOffset3D<float>;

  using Rect2D = BasicRect2D<unsigned>;
  using Rect2Df = BasicRect2D<float>;

  using Rect3D = BasicRect3D<unsigned>;
  using Rect3Df = BasicRect3D<float>;

  using Viewport = BasicViewport<float>;

}  // namespace utils