#pragma once
#include "../../../include/render/core.hpp"

namespace render
{
  // RenderImpl -------------------------------------------------------------------------------------------------------

  class RenderImpl
  {
   public:
    explicit RenderImpl(vulkan::Device device, RenderCreateFlags const& createFlags, vulkan::Image const& attachment);

    [[nodiscard]] vulkan::Device const& getDevice() const
    {
      return device_;
    }

    Command record(std::function<void(vulkan::CommandBuffer&)> const& obj)
    {
      return commands_.connect(obj);
    }

    void erase(Command const& command)
    {
      commands_.disconnect(command);
    }

    Command recordPostCommand(std::function<void(vulkan::CommandBuffer&)> const& obj)
    {
      return postCommands_.connect(obj);
    }

    void erasePostCommand(Command const& command)
    {
      postCommands_.disconnect(command);
    }

    vulkan::Semaphore render(std::vector<vulkan::WaitInfo> const& waitInfos);

   private:
    vulkan::Device device_;
    utils::signals::Signal<void(vulkan::CommandBuffer&)> commands_;
    utils::signals::Signal<void(vulkan::CommandBuffer&)> postCommands_;
    vulkan::Framebuffer framebuffer_;
    vulkan::RenderPass renderPass_;
    vulkan::ShaderState shaderState_;
    vulkan::RasterizationState rasterizationState_;
    vulkan::InputAssemblyState inputAssemblyState_;
    vulkan::DepthStencilState depthStencilState_;
    vulkan::ViewportState viewportState_;
    vulkan::VertexInputState vertexInputState_;
    vulkan::CommandBuffer commandBuffer_;
  };

}  // namespace render