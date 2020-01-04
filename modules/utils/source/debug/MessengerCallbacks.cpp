#include "MessengerCallbacks.hpp"
#include <iostream>

namespace utils::debug::messengerCallbacks
{
  void consoleDefault(std::string const &message, MessageSeverityFlagBits severity, MessageTypeFlags types)
  {
    std::cerr << magic_enum::enum_name(severity) << " " << types << " : \"" << message << "\"" << std::endl;
  }
}  // namespace utils::debug::messengerCallbacks