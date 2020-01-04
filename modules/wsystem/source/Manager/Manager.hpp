#pragma once
#include <utils/utils.hpp>
#include "../Window/Window.hpp"

namespace wsystem
{
  // utils ------------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(ManagerCreate, {};)

  // clang-format on

  enum class ManagerApi
  {
    Sdl
  };

  // Manager ----------------------------------------------------------------------------------------------------------

  class ManagerImpl;
  class BaseManager;

  class Manager
  {
   public:
    explicit Manager(const std::shared_ptr<BaseManager>& pbase);

    [[nodiscard]] std::shared_ptr<BaseManager> getBase() const;

    explicit Manager(ManagerApi api = ManagerApi::Sdl, ManagerCreateFlags createFlags = {});

    Window createWindow(std::string const& title, utils::Extent2D const& extent, WindowOptionsFlags options = {},
        WindowCreateFlags createFlags = {});

    void update();

   private:
    std::shared_ptr<ManagerImpl> pimpl_;
  };

}  // namespace wsystem