#pragma once
#include <functional>
#include <list>
#include <memory>

namespace utils::signals
{
  template <typename F_T>
  class Connection
  {
    template <typename T>
    friend bool operator==(Connection<T> const &lhs, Connection<T> const &rhs);

   public:
    Connection() = default;

    template <typename Slot_T>
    explicit Connection(Slot_T const &slot) : slot_(std::make_shared<std::function<F_T>>(slot))
    {
    }

    template <typename... Types>
    auto operator()(Types &&... args) const
    {
      return slot_->operator()(args...);
    }

   private:
    std::shared_ptr<std::function<F_T>> slot_;
  };

  template <typename F_T>
  bool operator==(Connection<F_T> const &lhs, Connection<F_T> const &rhs)
  {
    return lhs.slot_ == rhs.slot_;
  }

  template <typename F_T>
  bool operator!=(Connection<F_T> const &lhs, Connection<F_T> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename F_T>
  class Signal
  {
   public:
    void connect(Connection<F_T> slot)
    {
      slots_.push_back(slot);
    }

    template <typename Slot_T>
    Connection<F_T> connect(Slot_T const &slot)
    {
      Connection<F_T> connection(slot);
      slots_.push_back(connection);
      return connection;
    }

    template <typename Slot_T>
    void connectf(Slot_T const &slot)
    {
      slots_.emplace_back(slot);
    }

    void disconnect(Connection<F_T> slot)
    {
      auto findIt = std::find(slots_.cbegin(), slots_.cend(), slot);
      if (findIt != slots_.cend())
      {
        slots_.erase(findIt);
      }
    }

    template <typename... Types>
    void operator()(Types &&... args) const
    {
      for (auto slot : slots_)
      {
        slot(args...);
      }
    }

   private:
    std::list<Connection<F_T>> slots_;
  };

}  // namespace utils::signals