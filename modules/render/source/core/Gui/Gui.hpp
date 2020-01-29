#pragma once
#include <imgui.h>
#include "../utils.hpp"


namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  struct ShaderUiData {
    glm::vec2 scale;
    glm::vec2 translate;
  };

  struct GuiOptions
  {
    bool demoWindow = false;
  };

  // GuiImpl -------------------------------------------------------------------------------------------------------

  class GuiImpl
  {
   public:
    explicit GuiImpl(vulkan::Device device, wsystem::Window window);

    ~GuiImpl();

    void operator()(vulkan::CommandBuffer& commandBuffer);

   private:
    vulkan::Device device_;
    wsystem::Window window_;
    ImGuiIO& io_;
    vulkan::ShaderState shaderState_;
    vulkan::VertexInputState vertexInputState_;
    vulkan::DepthStencilState depthStencilState_;
    vulkan::ColorBlendState colorBlendState_;
    vulkan::Viewport viewport_;
    vulkan::ViewportState viewportState_;
    vulkan::Buffer uniformBuffer_;
    vulkan::BufferMappedData shaderUiData;
    ShaderUiData* pShaderUiData_;
    vulkan::Buffer vertexBuffer_{nullptr};
    vulkan::Buffer indexBuffer_{nullptr};
    Texture texture_;
    GuiOptions options_ = {};
  };

}  // namespace render