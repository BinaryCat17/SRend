#include "Tester.hpp"

namespace utils::debug
{
  // TestLayer ----------------------------------------------------------------------------------

  void TestLayer::call(Messenger const &messenger, const std::any &testStruct) const
  {
    for (auto const &callback : callbacks_)
    {
      callback(messenger, testStruct);
    }
  }

  // Tester -------------------------------------------------------------------------------------

  void Tester::submitTest(std::any const &testStruct) const
  {
    for (const auto &layer : layers_)
    {
      layer.call(messenger_, testStruct);
    }
  }

}  // namespace utils::debug