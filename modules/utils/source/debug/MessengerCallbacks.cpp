#include "MessengerCallbacks.hpp"
#include <iostream>

namespace utils::debug::messengerCallbacks
{
  void consoleDefault(std::string const &message, MessageSeverityFlagBits severity, MessageTypeFlags types)
  {
    std::string enumName = magic_enum::enum_name(severity).data();
    enumName[0] = static_cast<char>(std::toupper(enumName[0]));

    if (severity == MessageSeverityFlagBits::error || severity == MessageSeverityFlagBits::warning)
    {
      std::cerr << enumName << " " << types << " : \"" << message << "\"" << std::endl;
    }
    else
    {
      std::cout << enumName << " " << types << " : \"" << message << "\"" << std::endl;
    }
  }

}  // namespace utils::debug::messengerCallbacks