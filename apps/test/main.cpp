#include <iostream>
#include <wsystem/wsystem.hpp>

int main()
{
  wsystem::Manager manager;
  auto window = manager.createWindow("BAGAGAGAGAGAGGAGAGAGAG", utils::Extent2D{800, 600});

  bool shouldClose = false;
  window.onShouldClose().connectf([&shouldClose] {
    shouldClose = true;
    std::cout << "Close";
  });

  while (!shouldClose)
  {
    manager.update();
  }
}