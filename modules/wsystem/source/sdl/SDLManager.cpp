#include "SdlManager.hpp"
#include <SDL.h>
#include <SDL_vulkan.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <map>
#include <queue>
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

      std::deque<SDL_Event> pushEvents;

      SDL_Event evt = {};
      while (SDL_PollEvent(&evt))
      {
        switch (evt.type)
        {
          case SDL_WINDOWEVENT:
            ImGui_ImplSDL2_ProcessEvent(&evt);
            catchWindowEvents(get().windows_, evt);
            break;

          case SDL_KEYDOWN:
            if (evt.key.keysym.sym == SDLK_UP || evt.key.keysym.sym == SDLK_DOWN || evt.key.keysym.sym == SDLK_RIGHT ||
                evt.key.keysym.sym == SDLK_LEFT || evt.key.keysym.sym == SDLK_ESCAPE)
            {
              pushEvents.push_front(evt);
            }
            break;

          default:

            ImGui_ImplSDL2_ProcessEvent(&evt);
            break;
        }
      }

      for(auto & event : pushEvents)
      {
        SDL_PushEvent(&event);
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

  std::vector<char const*> SdlManager::getInstanceExtensions() const
  {
    unsigned count = 0;

    std::unique_ptr<SDL_Window, decltype(SDL_DestroyWindow)*> window(
        SDL_CreateWindow("test", 0, 0, 300, 300, SDL_WINDOW_HIDDEN | SDL_WINDOW_VULKAN), &SDL_DestroyWindow);

    if (!SDL_Vulkan_GetInstanceExtensions(window.get(), &count, nullptr))
    {
      throw std::runtime_error(SDL_GetError());
    }
    std::vector<char const*> extensions(count);
    if (!SDL_Vulkan_GetInstanceExtensions(nullptr, &count, extensions.data()))
    {
      throw std::runtime_error(SDL_GetError());
    }
    return extensions;
  }

}  // namespace wsystem