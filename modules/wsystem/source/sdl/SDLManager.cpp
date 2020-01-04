#include "SdlManager.hpp"
#include <SDL.h>
#include <map>
#include "SdlVulkan.hpp"
#include "SdlWindow.hpp"

namespace wsystem
{
  // utils ------------------------------------------------------------------------------------------------------------

  void catchWindowEvents(std::map<int, std::shared_ptr<SdlWindow>> const& windows, SDL_Event event)
  {
    auto window = windows.at(event.window.windowID);

    switch (event.window.event)
    {
      case SDL_WINDOWEVENT_RESIZED:
        window->setIsResized(true);
        break;
      case SDL_WINDOWEVENT_CLOSE:
        window->setIsShouldClose(true);
        break;
      case SDL_WINDOWEVENT_MOVED:
        window->setIsMoved(true);
        break;
      default:
        break;
    }
  }

  // SdlGlobalState ---------------------------------------------------------------------------------------------------

  class SdlGlobalState
  {
   public:
    static std::shared_ptr<SdlWindow> createWindow(
        std::string const& title, utils::Extent2D const& extent, WindowCreateFlags createOptions)
    {
      auto window = std::make_shared<SdlWindow>(title, extent, createOptions);
      get().windows_.emplace(SDL_GetWindowID(window->getSdlWindow().get()), window);
      return window;
    }

    static void removeWindow(const std::shared_ptr<SdlWindow>& window)
    {
      for (auto const& p : get().windows_)
      {
        if (p.second == window)
        {
          get().windows_.erase(SDL_GetWindowID(window->getSdlWindow().get()));
          return;
        }
      }

      throw std::runtime_error("Window not found");
    }

    static void update()
    {
      for (auto const& window : get().windows_)
      {
        window.second->setIsShouldClose(false);
        window.second->setIsResized(false);
        window.second->setIsMoved(false);
      }

      SDL_Event evt = {};
      while (SDL_PollEvent(&evt))
      {
        switch (evt.type)
        {
          case SDL_WINDOWEVENT:
            catchWindowEvents(get().windows_, evt);

          default:
            break;
        }
      }
    }

   private:
    SdlGlobalState()
    {
      SDL_Init(SDL_INIT_EVENTS);
    }

    static SdlGlobalState& get()
    {
      static SdlGlobalState initer;
      return initer;
    }

   private:
    std::map<int, std::shared_ptr<SdlWindow>> windows_;
  };

  // sdl_manager ------------------------------------------------------------------------------------------------------

  SdlManager::SdlManager(ManagerCreateFlags)
  {
  }

  std::shared_ptr<BaseWindow> SdlManager::createWindow(
      std::string const& title, utils::Extent2D const& extent, WindowCreateFlags createFlags)
  {
    return SdlGlobalState::createWindow(title, extent, createFlags);
  }

  void SdlManager::update()
  {
    SdlGlobalState::update();
  }

  void SdlManager::removeWindow(std::shared_ptr<BaseWindow> window)
  {
    SdlGlobalState::removeWindow(std::dynamic_pointer_cast<SdlWindow>(window));
  }

  std::shared_ptr<managerExtensions::VulkanImpl> SdlManager::extensionVulkan() const
  {
    return std::make_shared<managerExtensions::SdlVulkan>();
  }

}  // namespace wsystem