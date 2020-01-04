#pragma once
#include "../Buffer/BufferImpl.hpp"
#include "../Device/DeviceImpl.hpp"
#include "../Semaphore/SemaphoreImpl.hpp"
#include "CommandBuffer.hpp"

namespace vulkan
{
  // BaseCommandBufferImpl --------------------------------------------------------------------------------------------

  class BaseCommandBufferImpl : public virtual CommandBuffer
  {
   public:
    explicit BaseCommandBufferImpl(Device device, vk::CommandBuffer vkCommandBuffer);

    [[nodiscard]] Device const& getDeice() const
    {
      return device_;
    }

    [[nodiscard]] vk::CommandBuffer getVkCommandBuffer() const
    {
      return vkCommandBuffer_;
    }

    ~BaseCommandBufferImpl() override;

    void begin(CommandBufferUsageFlags const& usage) override;

   private:
    Device device_;
    vk::CommandBuffer vkCommandBuffer_;
  };

  // TransferCommandBufferImpl ----------------------------------------------------------------------------------------

  class TransferCommandBufferImpl : public virtual TransferCommandBuffer, public BaseCommandBufferImpl
  {
   public:
    using BaseCommandBufferImpl::BaseCommandBufferImpl;

    // buffer

    void copyBuffers(std::vector<BufferCopyInfo> const& copyInfos) override;

    void copyBuffer(std::shared_ptr<Buffer> const& srcBuffer, utils::OffsetT srcOffset,
        std::shared_ptr<Buffer> const& dstBuffer, utils::OffsetT dstOffset, utils::SizeT size) override;

    void copyBuffer(std::shared_ptr<Buffer> const& srcBuffer, std::shared_ptr<Buffer> const& dstBuffer) override;
  };

  // ComputeCommandBufferImpl -----------------------------------------------------------------------------------------

  class ComputeCommandBufferImpl : public virtual ComputeCommandBuffer, public BaseCommandBufferImpl
  {
   public:
    using BaseCommandBufferImpl::BaseCommandBufferImpl;
  };

  // GraphicCommandBufferImpl -----------------------------------------------------------------------------------------

  class GraphicCommandBufferImpl : public virtual GraphicCommandBuffer, public BaseCommandBufferImpl
  {
   public:
    using BaseCommandBufferImpl::BaseCommandBufferImpl;

    // render

    void draw(utils::IndexT firstVertex, utils::SizeT vertexCount, utils::IndexT firstInstance,
        utils::SizeT instanceCount) override;

    void drawIndexed(utils::IndexT firstIndex, utils::SizeT indexCount, utils::IndexT firstInstance,
        utils::SizeT instanceCount, utils::OffsetT vertexOffset) override;

    void setViewportState(std::vector<ViewportState> const& viewports) override;

    void setDepthStencilState(
        std::optional<DepthState> const& depthState, std::optional<StencilState> const& stencilState) override;

    // buffer

    void copyBuffers(std::vector<BufferCopyInfo> const& copyInfos) override;

    void copyBuffer(std::shared_ptr<Buffer> const& srcBuffer, utils::OffsetT srcOffset,
        std::shared_ptr<Buffer> const& dstBuffer, utils::OffsetT dstOffset, utils::SizeT size) override;

    void copyBuffer(std::shared_ptr<Buffer> const& srcBuffer, std::shared_ptr<Buffer> const& dstBuffer) override;

    void bindBuffers(std::vector<std::pair<std::shared_ptr<Buffer>, BindingInfo>> const& buffersBindingInfos) override;

    void bindBuffer(std::shared_ptr<Buffer> const& buffer, BindingInfo const& bindingInfo) override;
  };

}  // namespace vulkan