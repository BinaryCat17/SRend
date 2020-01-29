#include "Gui.hpp"
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include "../Texture/Texture.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  ImGuiIO& getImGuiIo(wsystem::Window const& window)
  {
    ImGui::CreateContext();
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_TitleBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.6f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 0.0f, 0.0f, 0.8f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
    style.Colors[ImGuiCol_Header] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);

    auto& io = ImGui::GetIO();

    io.DisplaySize = ImVec2(window.getSize().width(), window.getSize().height());
    io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
    return io;
  }

  Texture createFontTexture(vulkan::Device& device, ImGuiIO& io)
  {
    unsigned char* tex_pixels = nullptr;
    int tex_w, tex_h;
    io.Fonts->GetTexDataAsRGBA32(&tex_pixels, &tex_w, &tex_h);
    if (!tex_pixels)
    {
      throw std::runtime_error("fail to load font");
    }

    return Texture(device, tex_pixels, vulkan::Format::R8G8B8A8Unorm, utils::Extent2D(tex_w, tex_h),
        static_cast<utils::SizeT>(tex_w * tex_h * 4 * sizeof(char)));
  }

  vulkan::ShaderState createShaderStateUi(vulkan::Device const& device)
  {
    vulkan::ShaderState state(device);
    std::filesystem::path shaderPath("shaders");

    vulkan::Shader vertexShader(device);
    vertexShader.load(vulkan::ShaderType::Vertex, shaderPath / "vertui.spv");
    state.addShader(vertexShader);

    vulkan::Shader fragmentShader(device);
    fragmentShader.load(vulkan::ShaderType::Fragment, shaderPath / "fragui.spv");
    state.addShader(fragmentShader);

    return state;
  }

  vulkan::VertexInputState createVertexInputStateUi(vulkan::Device const& device)
  {
    vulkan::VertexInputState state(device);
    state.addInputBinding(vulkan::VertexInputRate::Vertex);
    state.addInputAttribute(vulkan::Format::R32G32Sfloat);
    state.addInputAttribute(vulkan::Format::R32G32Sfloat);
    state.addInputAttribute(vulkan::Format::R8G8B8A8Unorm);

    return state;
  }

  vulkan::DepthStencilState createDepthStencilStateUi(vulkan::Device const& device)
  {
    vulkan::DepthStencilState state(device);

    return state;
  }

  vulkan::Buffer createShaderUiDataBuffer(vulkan::Device& device, ImGuiIO& io)
  {
    ShaderUiData data = {};
    data.scale = glm::vec2(2.0f / io.DisplaySize.x, 2.0f / io.DisplaySize.y);
    data.translate = glm::vec2(-1.0f);
    return createUniformBuffer(device, &data, sizeof(ShaderUiData));
  }

  vulkan::ViewportState createViewportStateUi(vulkan::Device& device, vulkan::Viewport const& viewport)
  {
    vulkan::ViewportState viewportState(device);
    viewportState.addViewport(viewport);
    return viewportState;
  }

  vulkan::Viewport createViewportUi(vulkan::Device& device)
  {
    auto& io = ImGui::GetIO();

    vulkan::Viewport viewport(device, {});
    viewport.setExtent(utils::Extent2Df(io.DisplaySize.x, io.DisplaySize.y));
    viewport.setMinDepth(0);
    viewport.setMaxDepth(1);

    return viewport;
  }

  vulkan::ColorBlendState createColorBlendStateUi(vulkan::Device& device)
  {
    vulkan::ColorBlendState state(device);

    vulkan::ColorBlendAttachment info;
    info.srcColorBlendFactor = vulkan::BlendFactor::SrcAlpha;
    info.dstColorBlendFactor = vulkan::BlendFactor::OneMinusSrcAlpha;
    info.colorBlendOp = vulkan::BlendOp::Add;
    info.srcAlphaBlendFactor = vulkan::BlendFactor::OneMinusSrcAlpha;
    info.dstAlphaBlendFactor = vulkan::BlendFactor::Zero;
    info.alphaBlendOp = vulkan::BlendOp::Add;

    state.addAttachment(info);

    return state;
  }

  void updateGuiBuffers(vulkan::Device& device, vulkan::Buffer& vertexBuffer, vulkan::Buffer& indexBuffer)
  {
    auto imDrawData = ImGui::GetDrawData();
    if (imDrawData->TotalVtxCount)
    {
      vertexBuffer = createHostToDeviceBuffer(
          device, vulkan::BufferUsageFlagBits::VertexBuffer, nullptr, imDrawData->TotalVtxCount * sizeof(ImDrawVert));
      auto vertMappedData = vertexBuffer.mapMemory(vertexBuffer.getSize());
      auto pVertData = vertMappedData.pT<ImDrawVert>();

      indexBuffer = createHostToDeviceBuffer(
          device, vulkan::BufferUsageFlagBits::IndexBuffer, nullptr, imDrawData->TotalIdxCount * sizeof(ImDrawIdx));
      auto idxMappedData = indexBuffer.mapMemory(indexBuffer.getSize());
      auto pIdxData = idxMappedData.pT<ImDrawIdx>();

      for (int n = 0; n < imDrawData->CmdListsCount; n++)
      {
        const ImDrawList* cmd_list = imDrawData->CmdLists[n];
        memcpy(pVertData, cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));
        memcpy(pIdxData, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
        pVertData += cmd_list->VtxBuffer.Size;
        pIdxData += cmd_list->IdxBuffer.Size;
      }
    }
  }

  void recordGui(
      vulkan::CommandBuffer& commandBuffer, vulkan::Buffer const& vertexBuffer, vulkan::Buffer const& indexBuffer,
      vulkan::ViewportState& viewportState, vulkan::Viewport const& viewport)
  {
    // Render commands
    ImDrawData* imDrawData = ImGui::GetDrawData();
    if (imDrawData->TotalVtxCount)
    {
      int32_t vertexOffset = 0;
      int32_t indexOffset = 0;

      if (imDrawData->CmdListsCount > 0)
      {
        commandBuffer.bindVertexBuffer(vertexBuffer);
        commandBuffer.bindIndexBuffer(indexBuffer, vulkan::IndexType::Uint16);

        for (int32_t i = 0; i < imDrawData->CmdListsCount; i++)
        {
          const ImDrawList* cmd_list = imDrawData->CmdLists[i];
          for (int32_t j = 0; j < cmd_list->CmdBuffer.Size; j++)
          {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[j];
            utils::Rect2D scissorRect;
            scissorRect.setX(static_cast<utils::SizeT>(std::max(pcmd->ClipRect.x, 0.f)));
            scissorRect.setY(static_cast<utils::SizeT>(std::max(pcmd->ClipRect.y, 0.f)));
            scissorRect.setWidth(static_cast<utils::SizeT>(pcmd->ClipRect.z - pcmd->ClipRect.x));
            scissorRect.setHeight(static_cast<utils::SizeT>(pcmd->ClipRect.w - pcmd->ClipRect.y));
            viewportState.setScissor(viewport, scissorRect);
            commandBuffer.setViewportState(viewportState);

            commandBuffer.drawIndexed(indexOffset, pcmd->ElemCount, 0, 1, vertexOffset);
            indexOffset += pcmd->ElemCount;
          }
          vertexOffset += cmd_list->VtxBuffer.Size;
        }
      }
    }
  }

  // GuiImpl -------------------------------------------------------------------------------------------------------

  GuiImpl::GuiImpl(vulkan::Device device, wsystem::Window window)
      : device_(std::move(device)),
        window_(std::move(window)),
        io_(getImGuiIo(window_)),
        shaderState_(createShaderStateUi(device_)),
        vertexInputState_(createVertexInputStateUi(device_)),
        depthStencilState_(createDepthStencilStateUi(device_)),
        colorBlendState_(createColorBlendStateUi(device_)),
        viewport_(createViewportUi(device_)),
        viewportState_(createViewportStateUi(device_, viewport_)),
        uniformBuffer_(createShaderUiDataBuffer(device_, io_)),
        shaderUiData(uniformBuffer_.mapMemory(uniformBuffer_.getSize())),
        pShaderUiData_(shaderUiData.pT<ShaderUiData>()),
        texture_(createFontTexture(device_, io_))

  {
    ImGui_ImplSDL2_InitForVulkan(reinterpret_cast<SDL_Window*>(window_.getNativeHandle()));
  }

  GuiImpl::~GuiImpl()
  {
    ImGui::DestroyContext();
  }

  void GuiImpl::operator()(vulkan::CommandBuffer& commandBuffer)
  {
    window_.onResize().connect([this]{
      auto& io = ImGui::GetIO();
      io.DisplaySize = ImVec2(window_.getSize().width(), window_.getSize().height());
      viewport_ = createViewportUi(device_);
      viewportState_ = createViewportStateUi(device_, viewport_);
      pShaderUiData_->scale = glm::vec2(2.0f / io.DisplaySize.x, 2.0f / io.DisplaySize.y);
    });

    ImGui_ImplSDL2_NewFrame(reinterpret_cast<SDL_Window*>(window_.getNativeHandle()));
    commandBuffer.setShaderState(shaderState_);
    commandBuffer.setVertexInputState(vertexInputState_);
    commandBuffer.setDepthStencilState(depthStencilState_);
    commandBuffer.setColorBlendState(colorBlendState_);
    commandBuffer.bindBuffer(uniformBuffer_, vulkan::BindingInfo(1));
    (*texture_.getImpl())(commandBuffer, vulkan::BindingInfo(0));
    updateGuiBuffers(device_, vertexBuffer_, indexBuffer_);
    recordGui(commandBuffer, vertexBuffer_, indexBuffer_, viewportState_, viewport_);
  }

  // Gui -----------------------------------------------------------------------------------------------------------

  Gui::Gui(vulkan::Device const& device, wsystem::Window const& window)
      : pimpl_(std::make_shared<GuiImpl>(device, window))
  {
  }

  void Gui::operator()(vulkan::CommandBuffer& commandBuffer)
  {
    pimpl_->operator()(commandBuffer);
  }

}  // namespace render