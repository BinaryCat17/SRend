#include "../Window/WindowImpl.hpp"
#include "../sdl/SdlManager.hpp"

namespace wsystem
{
  // utils ------------------------------------------------------------------------------------------------------------

  std::shared_ptr<BaseManager> createBaseManager(ManagerApi api, ManagerCreateFlags createFlags)
  {
    switch (api)
    {
      case wsystem::ManagerApi::Sdl:
        return std::make_shared<SdlManager>(createFlags);

      default:
        throw std::runtime_error("undefined manager API");
    }
  }

  // ManagerImpl ------------------------------------------------------------------------------------------------------

  class ManagerImpl
  {
   public:
    explicit ManagerImpl(std::shared_ptr<BaseManager> pbase) : pbase_(std::move(pbase))
    {
    }

    [[nodiscard]] std::shared_ptr<BaseManager> getBase() const
    {
      return pbase_;
    }

    ManagerImpl(ManagerApi api, ManagerCreateFlags createFlags) : pbase_(createBaseManager(api, createFlags))
    {
    }

    Window createWindow(std::string const& title, utils::Extent2D const& extent, WindowOptionsFlags options,
        WindowCreateFlags createFlags)
    {
      auto window = std::make_shared<WindowImpl>(pbase_->createWindow(title, extent, createFlags), pbase_);
      window->applyOptions(options);
      windows_.push_back(window);
      return Window(window);
    }

    void update()
    {
      pbase_->update();
      for (const auto& window : windows_)
      {
        window->update();
      }
    }

    [[nodiscard]] managerExtensions::Vulkan extensionVulkan() const
    {
      return managerExtensions::Vulkan(pbase_->extensionVulkan());
    }

   private:
    std::shared_ptr<BaseManager> pbase_;
    std::list<std::shared_ptr<WindowImpl>> windows_;
  };

  // Manager ----------------------------------------------------------------------------------------------------------

  Manager::Manager(const std::shared_ptr<BaseManager>& pbase) : pimpl_(std::make_shared<ManagerImpl>(pbase))
  {
  }

  std::shared_ptr<BaseManager> Manager::getBase() const
  {
    return pimpl_->getBase();
  }

  Manager::Manager(ManagerApi api, ManagerCreateFlags createFlags)
      : pimpl_(std::make_shared<ManagerImpl>(api, createFlags))
  {
  }

  Window Manager::createWindow(std::string const& title, utils::Extent2D const& extent, WindowOptionsFlags options,
      WindowCreateFlags createFlags)
  {
    return pimpl_->createWindow(title, extent, options, createFlags);
  }

  void Manager::update()
  {
    pimpl_->update();
  }

}  // namespace wsystem
