#pragma once
#include "../../../include/render/core.hpp"

namespace render
{
  // PresenterImpl ----------------------------------------------------------------------------------------------------

  class PresenterImpl
  {
   public:
    explicit PresenterImpl(vulkan::Device const& device, utils::Extent2D const& extent);

    Command record(std::function<void(vulkan::CommandBuffer&)> const& obj)
    {
      return commands_.connect(obj);
    }

    void erase(Command const& command)
    {
      render_.erase(command);
    }

    Command recordPostCommand(std::function<void(vulkan::CommandBuffer&)> const& obj)
    {
      return postCommands_.connect(obj);
    }

    void erasePostCommand(Command const& command)
    {
      postCommands_.disconnect(command);
    }

    void runLoop();

    [[nodiscard]] wsystem::Window getWindow() const
    {
      return window_;
    }

   private:
    vulkan::Device device_;
    vulkan::Image attachment_;
    Render render_;
    wsystem::Manager manager_;
    wsystem::Window window_;
    vulkan::presentation::RenderWindow vulkanWindow_;
    utils::signals::Signal<void(vulkan::CommandBuffer&)> commands_;
    utils::signals::Signal<void(vulkan::CommandBuffer&)> postCommands_;
  };

}  // namespace render