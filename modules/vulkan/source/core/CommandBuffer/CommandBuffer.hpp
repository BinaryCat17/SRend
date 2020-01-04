#pragma once
#include "../Buffer/Buffer.hpp"
#include "../Device/Device.hpp"
#include "../Semaphore/Semaphore.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(CommandBufferCreate, {};)

  SR_MAKE_BIT_FLAGS(CommandBufferUsage, {
    OneTimeSubmit,
    SimultaneousUse
  };)

  SR_MAKE_BIT_FLAGS(WaitStage, {
    AllCommands,
    AllGraphics,
    TopOfPipe,
    BottomOfPipe,
    VertexInput,
    VertexShader,
    FragmentShader,
    EarlyFragmentTests,
    LateFragmentTests,
    GeometryShader,
    TessellationControlShader,
    TessellationEvaluationShader,
    ComputeShader,
    Host,
    Transfer,
    ColorAttachmentOutput
  };)

  // clang-format on

  enum class StencilOp
  {
    Keep,
    Zero,
    Replace,
    IncrementAndClamp,
    DecrementAndClamp,
    Invert,
    IncrementAndWrap,
    DecrementAndWrap
  };

  enum class CompareOp
  {
    Never,
    Less,
    Equal,
    LessOrEqual,
    Greater,
    NotEqual,
    GreaterOrEqual,
    Always
  };

  struct DepthState
  {
    DepthState() = default;

    DepthState(bool writeEnable, CompareOp compareOp, bool boundsTestEnable)
        : writeEnable(writeEnable), compareOp(compareOp), boundsTestEnable(boundsTestEnable)
    {
    }

    bool writeEnable = false;
    CompareOp compareOp = CompareOp::LessOrEqual;
    bool boundsTestEnable = false;
  };

  struct StencilOpInfo
  {
    StencilOpInfo() = default;

    StencilOpInfo(StencilOp failOp, StencilOp passOp, StencilOp depthFailOp, CompareOp compareOp)
        : failOp(failOp), passOp(passOp), depthFailOp(depthFailOp), compareOp(compareOp)
    {
    }

    StencilOp failOp = StencilOp::Keep;
    StencilOp passOp = StencilOp::Keep;
    StencilOp depthFailOp = StencilOp::Keep;
    CompareOp compareOp = CompareOp::LessOrEqual;
  };

  struct StencilState
  {
    StencilState() = default;

    StencilState(StencilOpInfo const& front, StencilOpInfo const& back) : front(front), back(back)
    {
    }

    StencilOpInfo front;
    StencilOpInfo back;
  };

  struct ViewportState
  {
    ViewportState() = default;

    explicit ViewportState(utils::Viewport const& viewport, utils::Rect2D const& scissor)
        : viewport(viewport), scissor(scissor)
    {
    }

    utils::Viewport viewport;
    utils::Rect2D scissor;
  };

  struct BufferCopyInfo
  {
    BufferCopyInfo() = default;

    BufferCopyInfo(std::shared_ptr<Buffer> srcBuffer, utils::OffsetT srcOffset, std::shared_ptr<Buffer> dstBuffer,
        utils::OffsetT dstOffset, utils::SizeT size)
        : srcBuffer(std::move(srcBuffer)),
          srcOffset(srcOffset),
          dstBuffer(std::move(dstBuffer)),
          dstOffset(dstOffset),
          size(size)
    {
    }

    BufferCopyInfo(std::shared_ptr<Buffer> srcBuffer, std::shared_ptr<Buffer> dstBuffer, utils::SizeT size)
        : srcBuffer(std::move(srcBuffer)), dstBuffer(std::move(dstBuffer)), size(size)
    {
    }

    std::shared_ptr<Buffer> srcBuffer;
    utils::OffsetT srcOffset = 0;
    std::shared_ptr<Buffer> dstBuffer;
    utils::OffsetT dstOffset = 0;
    utils::SizeT size = 0;
  };

  struct WaitInfo
  {
    WaitInfo(Semaphore semaphore, WaitStageFlags waitStages) : semaphore(std::move(semaphore)), waitStages(waitStages)
    {
    }

    Semaphore semaphore;
    WaitStageFlags waitStages;
  };

  struct BindingInfo
  {
    BindingInfo() = default;

    BindingInfo(utils::IndexT binding, utils::IndexT index, utils::IndexT set)
        : binding(binding), index(index), set(set)
    {
    }

    utils::IndexT binding = 0;
    utils::IndexT index = 0;
    utils::IndexT set = 0;
  };

  // CommandBuffer ----------------------------------------------------------------------------------------------------

  class CommandBuffer
  {
   public:
    virtual ~CommandBuffer() = default;

    virtual void begin(CommandBufferUsageFlags const& usage) = 0;
  };

  // TransferCommandBuffer --------------------------------------------------------------------------------------------

  class TransferCommandBuffer : public virtual CommandBuffer
  {
   public:
    // buffer

    virtual void copyBuffers(std::vector<BufferCopyInfo> const& copyInfos) = 0;

    virtual void copyBuffer(std::shared_ptr<Buffer> const& srcBuffer, utils::OffsetT srcOffset,
        std::shared_ptr<Buffer> const& dstBuffer, utils::OffsetT dstOffset, utils::SizeT size) = 0;

    virtual void copyBuffer(std::shared_ptr<Buffer> const& srcBuffer, std::shared_ptr<Buffer> const& dstBuffer) = 0;
  };

  std::vector<std::shared_ptr<TransferCommandBuffer>> allocateTransferCommandBuffers(
      Device const& device, CommandBufferCreateFlags const& createFlags, utils::SizeT count);

  std::shared_ptr<TransferCommandBuffer> allocateTransferCommandBuffer(
      Device const& device, CommandBufferCreateFlags const& createFlags);

  std::vector<Semaphore> submitCommandBuffers(
      std::vector<std::pair<std::shared_ptr<TransferCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos);

  Semaphore submitCommandBuffer(
      std::shared_ptr<TransferCommandBuffer> const& commandBuffer, std::vector<WaitInfo> const& waitInfos);

  // ComputeCommandBuffer ---------------------------------------------------------------------------------------------

  class ComputeCommandBuffer : public virtual CommandBuffer
  {
   public:
  };

  std::vector<std::shared_ptr<ComputeCommandBuffer>> allocateComputeCommandBuffers(
      Device const& device, CommandBufferCreateFlags const& createFlags, utils::SizeT count);

  std::shared_ptr<ComputeCommandBuffer> allocateComputeCommandBuffer(
      Device const& device, CommandBufferCreateFlags const& createFlags);

  std::vector<Semaphore> submitCommandBuffers(
      std::vector<std::pair<std::shared_ptr<ComputeCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos);

  Semaphore submitCommandBuffer(
      std::shared_ptr<ComputeCommandBuffer> const& commandBuffer, std::vector<WaitInfo> const& waitInfos);

  // GraphicCommandBuffer ---------------------------------------------------------------------------------------------

  class GraphicCommandBuffer : public ComputeCommandBuffer, public TransferCommandBuffer
  {
   public:
    // render

    virtual void draw(utils::IndexT firstVertex, utils::SizeT vertexCount, utils::IndexT firstInstance,
        utils::SizeT instanceCount) = 0;

    virtual void drawIndexed(utils::IndexT firstIndex, utils::SizeT indexCount, utils::IndexT firstInstance,
        utils::SizeT instanceCount, utils::OffsetT vertexOffset) = 0;

    virtual void setViewportState(std::vector<ViewportState> const& viewports) = 0;

    virtual void setDepthStencilState(
        std::optional<DepthState> const& depthState, std::optional<StencilState> const& stencilState) = 0;

    // buffer

    virtual void bindBuffers(
        std::vector<std::pair<std::shared_ptr<Buffer>, BindingInfo>> const& buffersBindingInfos) = 0;

    virtual void bindBuffer(std::shared_ptr<Buffer> const& buffer, BindingInfo const& bindingInfo) = 0;
  };

  std::vector<std::shared_ptr<GraphicCommandBuffer>> allocateGraphicCommandBuffers(
      Device const& device, CommandBufferCreateFlags const& createFlags, utils::SizeT count);

  std::shared_ptr<GraphicCommandBuffer> allocateGraphicCommandBuffer(
      Device const& device, CommandBufferCreateFlags const& createFlags);

  std::vector<Semaphore> submitCommandBuffers(
      std::vector<std::pair<std::shared_ptr<GraphicCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos);

  Semaphore submitCommandBuffer(
      std::shared_ptr<GraphicCommandBuffer> commandBuffer, std::vector<WaitInfo> const& waitInfos);

}  // namespace vulkan