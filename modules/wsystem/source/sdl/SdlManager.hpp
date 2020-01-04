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
    [[nodiscard]] std::shared_ptr<managerExtensions::VulkanImpl> extensionVulkan() const override;
    void update() override;
  };

}  // namespace wsystem