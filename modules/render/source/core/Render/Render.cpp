#include "Render.hpp"
#include "../../../include/render/core.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  vulkan::Framebuffer createFramebuffer(vulkan::Device const& device, vulkan::Image const& attachment)
  {
    vulkan::Image depthAttachment(device, {}, attachment.getExtent(), vulkan::Format::D32Sfloat,
        vulkan::ImageUsageFlagBits::DepthStencilAttachment);
    vulkan::Framebuffer framebuffer(device);
    framebuffer.addAttachment(attachment);
    framebuffer.addAttachment(depthAttachment);
    return framebuffer;
  }

  vulkan::RenderPass createRenderPass(vulkan::Device const& device)
  {
    vulkan::RenderPass renderPass(device);
    renderPass.addAttachment(vulkan::ColorClearValue());
    renderPass.addAttachment(vulkan::DepthClearValue());
    return renderPass;
  }

  vulkan::CommandBuffer createCommandBuffer(vulkan::Device const& device)
  {
    return vulkan::CommandBuffer(device, {}, vulkan::CommandBufferType::Graphic);
  }

  vulkan::DepthStencilState createDepthStencilState(vulkan::Device const& device)
  {
    vulkan::DepthStencilState state(device);
    state.setDepthTest(true);
    state.setDepthWrite(true);
    state.setDepthCompareOp(vulkan::CompareOp::Less);

    return state;
  }

  vulkan::RasterizationState createRasterizationState(vulkan::Device const& device)
  {
    vulkan::RasterizationState state(device);
    return state;
  }

  vulkan::InputAssemblyState createInputAssemblyState(vulkan::Device const& device)
  {
    vulkan::InputAssemblyState state(device);
    state.setPrimitiveTopology(vulkan::PrimitiveTopology::TriangleList);
    return state;
  }

  vulkan::ViewportState createViewportState(vulkan::Device const& device, utils::Extent3D const& imageExtent)
  {
    vulkan::ViewportState viewportState(device);
    vulkan::Viewport viewport(device, {});
    viewport.setExtent(utils::Extent2Df(imageExtent.width(), imageExtent.height()));
    viewport.setMinDepth(0);
    viewport.setMaxDepth(1);
    viewportState.addViewport(viewport);
    return viewportState;
  }

  vulkan::ShaderState createShaderState(vulkan::Device const& device)
  {
    vulkan::ShaderState state(device);
    std::filesystem::path shaderPath("shaders");

    vulkan::Shader vertexShader(device);
    vertexShader.load(vulkan::ShaderType::Vertex, shaderPath / "vert.spv");
    state.addShader(vertexShader);

    vulkan::Shader fragmentShader(device);
    fragmentShader.load(vulkan::ShaderType::Fragment, shaderPath / "frag.spv");
    state.addShader(fragmentShader);

    return state;
  }

  vulkan::VertexInputState createVertexInputState(vulkan::Device const& device)
  {
    vulkan::VertexInputState state(device);
    state.addInputBinding(vulkan::VertexInputRate::Vertex);
    state.addInputAttribute(vulkan::Format::R32G32B32Sfloat);
    state.addInputAttribute(vulkan::Format::R32G32B32Sfloat);
    state.addInputAttribute(vulkan::Format::R32G32Sfloat);

    return state;
  }

  // RenderImpl -------------------------------------------------------------------------------------------------------

  RenderImpl::RenderImpl(vulkan::Device device, RenderCreateFlags const&, vulkan::Image const& attachment)
      : device_(std::move(device)),
        framebuffer_(createFramebuffer(device_, attachment)),
        renderPass_(createRenderPass(device_)),
        shaderState_(createShaderState(device_)),
        rasterizationState_(createRasterizationState(device_)),
        inputAssemblyState_(createInputAssemblyState(device_)),
        depthStencilState_(createDepthStencilState(device_)),
        viewportState_(createViewportState(device_, attachment.getExtent())),
        vertexInputState_(createVertexInputState(device_)),
        commandBuffer_(createCommandBuffer(device_))
  {
  }

  vulkan::Semaphore RenderImpl::render(std::vector<vulkan::WaitInfo> const& waitInfos)
  {
    commandBuffer_.begin(vulkan::CommandBufferBeginFlagBits::OneTimeSubmit);
    commandBuffer_.beginRender(framebuffer_, renderPass_);
    commandBuffer_.setRasterizationState(rasterizationState_);
    commandBuffer_.setInputAssemblyState(inputAssemblyState_);
    commandBuffer_.setDepthStencilState(depthStencilState_);
    commandBuffer_.setShaderState(shaderState_);
    commandBuffer_.setViewportState(viewportState_);
    commandBuffer_.setVertexInputState(vertexInputState_);
    commands_.operator()(commandBuffer_);
    auto submitSemaphore = commandBuffer_.submit(waitInfos);

    postCommands_(commandBuffer_);

    return submitSemaphore;
  }

  // Render -----------------------------------------------------------------------------------------------------------

  Render::Render(vulkan::Device const& device, RenderCreateFlags const& createFlags, vulkan::Image const& attachment)
      : pimpl_(std::make_shared<RenderImpl>(device, createFlags, attachment))
  {
  }

  Command Render::record(std::function<void(vulkan::CommandBuffer&)> const& obj)
  {
    return pimpl_->record(obj);
  }

  void Render::erase(Command const& command)
  {
    pimpl_->erase(command);
  }

  vulkan::Semaphore Render::render(std::vector<vulkan::WaitInfo> const& waitInfos)
  {
    return pimpl_->render(waitInfos);
  }

  Command Render::recordPostCommand(std::function<void(vulkan::CommandBuffer&)> const& obj)
  {
    return pimpl_->recordPostCommand(obj);
  }

  void Render::erasePostCommand(Command const& command)
  {
    pimpl_->erasePostCommand(command);
  }

}  // namespace render