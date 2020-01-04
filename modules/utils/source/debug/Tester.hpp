#pragma once
#include <any>
#include "Messenger.hpp"

namespace utils::debug
{
  // util classes -----------------------------------------------------------------------------------------------------

  using TestCallback = std::function<void(Messenger const &messenger, std::any const &testStruct)>;

  // TestLayer --------------------------------------------------------------------------------------------------------

  class TestLayer
  {
   public:
    TestLayer() = default;

    explicit TestLayer(std::vector<TestCallback> callbacks) : callbacks_(std::move(callbacks))
    {
    }

    template <typename F>
    void addCallback(F const &callback)
    {
      callbacks_.emplace_back(callback);
    }

    template <typename F>
    void addCallbacks(std::vector<F> const &callbacks)
    {
      callbacks_.insert(callbacks_.cend(), callbacks.cbegin(), callbacks.cend());
    }

    void call(Messenger const &messenger, const std::any &testStruct) const;

   private:
    std::vector<TestCallback> callbacks_;
  };

  // Tester -------------------------------------------------------------------------------------

  class Tester
  {
   public:
    Tester() = default;

    explicit Tester(std::vector<TestLayer> testLayers, Messenger messenger = Messenger())
        : layers_(std::move(testLayers)), messenger_(std::move(messenger))
    {
    }

    void setMessenger(Messenger const &messenger)
    {
      messenger_ = messenger;
    }

    void addTestLayer(TestLayer const &layer)
    {
      layers_.push_back(layer);
    }

    void addTestLayers(std::vector<TestLayer> const &layers)
    {
      layers_.insert(layers_.cend(), layers.cbegin(), layers.cend());
    }

    void submitTest(std::any const &testStruct) const;

   private:
    std::vector<TestLayer> layers_;
    Messenger messenger_;
  };

}  // namespace utils::debug