#pragma once
#include "Messenger.hpp"

namespace utils::debug::messengerCallbacks
{
  void consoleDefault(std::string const &message, MessageSeverityFlagBits severity, MessageTypeFlags types);
}  // namespace utils::debug::messengerCallbacks