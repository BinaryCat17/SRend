#pragma once
#include <functional>
#include <string>
#include "../flagsUtils/flagsUtils.hpp"

namespace utils::debug
{
  // util classes -----------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(MessageSeverity, {
    error = 1u << 0u,
    warning = 1u << 1u,
    info = 1u << 2u,
    notice = 1u << 3u
  };)

  SR_MAKE_BIT_FLAGS(MessageType, {
    performance = 1u << 0u,
    validation = 1u << 1u,
    general = 1u << 2u
  };)

  // clang-format on

  using MessengerCallback =
      std::function<void(std::string const &message, MessageSeverityFlagBits severity, MessageTypeFlags types)>;

  // Messenger --------------------------------------------------------------------------------------------------------

  class Messenger
  {
   public:
    explicit Messenger(MessengerCallback callback,
        MessageSeverityFlags severityFilter = MessageSeverityFlagBits::notice | MessageSeverityFlagBits::info |
                                              MessageSeverityFlagBits::warning | MessageSeverityFlagBits::error,
        MessageTypeFlags typeFilter = MessageTypeFlagBits::general | MessageTypeFlagBits::validation |
                                      MessageTypeFlagBits::performance);

    explicit Messenger(MessageSeverityFlags severityFilter,
        MessageTypeFlags typeFilter = MessageTypeFlagBits::general | MessageTypeFlagBits::validation |
                                      MessageTypeFlagBits::performance);

    Messenger();

    void report(std::string const &message, MessageSeverityFlagBits severity, MessageTypeFlags types) const;

    [[nodiscard]] MessageSeverityFlags severityFilter() const
    {
      return severityFilter_;
    }

    [[nodiscard]] MessageTypeFlags typeFilter() const
    {
      return typeFilter_;
    }

   private:
    MessageSeverityFlags severityFilter_;
    MessageTypeFlags typeFilter_;
    MessengerCallback callback_;
  };
}  // namespace utils::debug