#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // CommandBufferImpl ------------------------------------------------------------------------------------------------

  class CommandBufferImpl
  {
   public:
    explicit CommandBufferImpl(std::shared_ptr<DeviceImpl> device, vk::CommandBuffer vkCommandBuffer);

    CommandBufferImpl(CommandBufferImpl const&) = delete;

    CommandBufferImpl(CommandBufferImpl&&) = delete;

    CommandBufferImpl& operator=(CommandBufferImpl const&) = delete;

    CommandBufferImpl& operator=(CommandBufferImpl&&) = delete;

    ~CommandBufferImpl();

    [[nodiscard]] std::shared_ptr<DeviceImpl> const& getDevice() const
    {
      return device_;
    }

    [[nodiscard]] vk::CommandBuffer getVkCommandBuffer() const
    {
      return vkCommandBuffer_;
    }

    void begin(CommandBufferBeginFlags const& beginFlags);

    void end();

    void beginRender(Framebuffer const& framebuffer, RenderPass const& renderPass);

    void endRender();

    // Graphic commands

    void setShaderState(ShaderState const& state);

    void setVertexInputState(VertexInputState const& state);

    void setInputAssemblyState(InputAssemblyState const& state);

    void setRasterizationState(RasterizationState const& state);

    void setMultisampleState(MultisampleState const& state);

    void setDepthStencilState(DepthStencilState const& state);

    void setViewportState(ViewportState const& state);

    void setColorBlendState(ColorBlendState const& state);

    void draw(utils::IndexT firstVertex, utils::SizeT vertexCount, utils::IndexT firstInstance = 0,
        utils::SizeT instanceCount = 1);

    void drawIndexed(utils::IndexT firstIndex, utils::SizeT indexCount, utils::IndexT firstInstance = 0,
        utils::SizeT instanceCount = 1, utils::OffsetT vertexOffset = 0);

    void bindBuffer(Buffer const& buffer, BindingInfo const& bindingInfo);

    void bindImage(Image const& image, Sampler const& sampler, BindingInfo const& bindingInfo);

    // Transfer commands

    void copyBuffer(Buffer const& srcBuffer, utils::OffsetT srcOffset, Buffer const& dstBuffer,
        utils::OffsetT dstOffset, utils::SizeT size);

    void copyImage(Image const& srcImage, utils::Offset3D const& srcOffset, ImageSubResourceRange const& srcSubResource,
        Image const& dstImage, utils::Offset3D const& dstOffset, ImageSubResourceRange const& dstSubResource,
        utils::Extent3D const& extent);

    void copyBufferToImage(Buffer const& buffer, utils::OffsetT bufferOffset, utils::SizeT bufferRowLength,
        utils::SizeT bufferImageHeight, Image const& image, ImageSubResourceRange const& imageSubResource,
        utils::Offset3D const& imageOffset, utils::Extent3D const& imageExtent);

   private:
    std::shared_ptr<DeviceImpl> device_;
    vk::CommandBuffer vkCommandBuffer_;
  };

}  // namespace vulkan