#pragma once
#include "../Manager/BaseManager.hpp"

namespace wsystem
{
  // SdlManager -----------------------------------------------------------------------------------

  class SdlManager : public BaseManager
  {
   public:
    explicit SdlManager(ManagerCreateFlags createFlags);

    std::shared_ptr<BaseWindow> createWindow(
        std::string const& title, utils::Extent2D const& extent, WindowCreateFlags createFlags) override;

    void removeWindow(std::shared_ptr<BaseWindow> window) override;

    void update() override;

    [[nodiscard]] std::vector<char const*> getInstanceExtensions() const override;
  };

}  // namespace wsystem