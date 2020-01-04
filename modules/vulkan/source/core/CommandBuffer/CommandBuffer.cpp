#include "../Semaphore/SemaphoreImpl.hpp"
#include "CommandBufferImpl.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  template <typename T>
  std::vector<VkCommandBuffer> toVkCommandBuffers(std::vector<std::pair<T, std::vector<WaitInfo>>> const& submitInfos)
  {
    std::vector<VkCommandBuffer> result;
    result.reserve(submitInfos.size());

    for (auto const& info : submitInfos)
    {
      result.push_back(implCast<BaseCommandBufferImpl>(info.first)->getVkCommandBuffer());
    }

    return result;
  }

  template <typename T>
  std::vector<VkSemaphore> toVkSemaphores(std::vector<std::pair<T, std::vector<WaitInfo>>> const& submitInfos)
  {
    std::vector<VkSemaphore> result;

    for (auto const& info : submitInfos)
    {
      for (auto const& waitInfo : info.second)
      {
        result.push_back(waitInfo.semaphore.getImpl()->getVkSemaphore());
      }
    }

    return result;
  }

  template <typename T>
  std::vector<VkPipelineStageFlags> toVkWaitStages(std::vector<std::pair<T, std::vector<WaitInfo>>> const& submitInfos)
  {
    std::vector<VkPipelineStageFlags> result;

    for (auto const& info : submitInfos)
    {
      for (auto const& waitInfo : info.second)
      {
        VkPipelineStageFlags flags = 0;

        if (waitInfo.waitStages & WaitStageFlagBits::AllCommands)
        {
          flags |= VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::AllGraphics)
        {
          flags |= VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::TopOfPipe)
        {
          flags |= VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::BottomOfPipe)
        {
          flags |= VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::VertexInput)
        {
          flags |= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::VertexShader)
        {
          flags |= VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::FragmentShader)
        {
          flags |= VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::EarlyFragmentTests)
        {
          flags |= VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::LateFragmentTests)
        {
          flags |= VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::GeometryShader)
        {
          flags |= VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::TessellationControlShader)
        {
          flags |= VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::TessellationEvaluationShader)
        {
          flags |= VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::ComputeShader)
        {
          flags |= VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::Host)
        {
          flags |= VK_PIPELINE_STAGE_HOST_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::Transfer)
        {
          flags |= VK_PIPELINE_STAGE_TRANSFER_BIT;
        }
        if (waitInfo.waitStages & WaitStageFlagBits::ColorAttachmentOutput)
        {
          flags |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        }

        result.push_back(flags);
      }
    }

    return result;
  }

  template <typename T, typename TImpl>
  std::vector<std::shared_ptr<T>> allocateBaseCommandBuffers(Device const& device, vk::Queue queue, utils::SizeT count)
  {
    VezCommandBufferAllocateInfo allocInfo = {};
    allocInfo.queue = queue;
    allocInfo.commandBufferCount = static_cast<uint32_t>(count);

    std::vector<vk::CommandBuffer> vkCommandBuffers(count);
    checkResult(vezAllocateCommandBuffers(
        device.getImpl()->getVkDevice(), &allocInfo, reinterpret_cast<VkCommandBuffer*>(vkCommandBuffers.data())));

    std::vector<std::shared_ptr<T>> result;
    result.reserve(vkCommandBuffers.size());

    for (auto vkCommandBuffer : vkCommandBuffers)
    {
      result.push_back(std::make_shared<TImpl>(device, vkCommandBuffer));
    }

    return result;
  }

  template <typename T>
  std::vector<Semaphore> submitBaseCommandBuffers(vk::Device device, vk::Queue queue,
      std::vector<std::pair<std::shared_ptr<T>, std::vector<WaitInfo>>> const& submitInfos)
  {
    vezEndCommandBuffer();

    std::vector<vk::Semaphore> signalSemaphores(submitInfos.size());
    std::vector<VkCommandBuffer> commandBuffers = toVkCommandBuffers(submitInfos);
    std::vector<VkSemaphore> waitSemaphores = toVkSemaphores(submitInfos);
    std::vector<VkPipelineStageFlags> waitStages = toVkWaitStages(submitInfos);

    VezSubmitInfo vkSubmitInfo = {};
    vkSubmitInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());
    vkSubmitInfo.pCommandBuffers = commandBuffers.data();
    vkSubmitInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
    vkSubmitInfo.pWaitSemaphores = waitSemaphores.data();
    vkSubmitInfo.pWaitDstStageMask = waitStages.data();
    vkSubmitInfo.signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores.size());
    vkSubmitInfo.pSignalSemaphores = reinterpret_cast<VkSemaphore*>(signalSemaphores.data());

    VkFence waitFence = nullptr;
    checkResult(vezQueueSubmit(queue, 1, &vkSubmitInfo, &waitFence));
    checkResult(vezWaitForFences(device, 1, &waitFence, true, UINT64_MAX));
    vezDestroyFence(device, waitFence);

    std::vector<Semaphore> result;
    result.reserve(signalSemaphores.size());

    for (auto const& semaphore : signalSemaphores)
    {
      result.emplace_back(std::make_shared<SemaphoreImpl>(semaphore));
    }

    return result;
  }

  // TransferCommandBuffer --------------------------------------------------------------------------------------------

  std::vector<std::shared_ptr<TransferCommandBuffer>> allocateTransferCommandBuffers(
      Device const& device, CommandBufferCreateFlags const&, utils::SizeT count)
  {
    return allocateBaseCommandBuffers<TransferCommandBuffer, TransferCommandBufferImpl>(
        device, device.getImpl()->getQueues().transferQueue, count);
  }

  std::shared_ptr<TransferCommandBuffer> allocateTransferCommandBuffer(
      Device const& device, CommandBufferCreateFlags const& createFlags)
  {
    return allocateTransferCommandBuffers(device, createFlags, 1).front();
  }

  std::vector<Semaphore> submitCommandBuffers(
      std::vector<std::pair<std::shared_ptr<TransferCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos)
  {
    auto device = implCast<BaseCommandBufferImpl>(submitInfos.front().first)->getDeice().getImpl();

    return submitBaseCommandBuffers(device->getVkDevice(), device->getQueues().transferQueue, submitInfos);
  }

  Semaphore submitCommandBuffer(
      std::shared_ptr<TransferCommandBuffer> const& commandBuffer, std::vector<WaitInfo> const& waitInfos)
  {
    return submitCommandBuffers(std::vector{std::pair{commandBuffer, waitInfos}}).front();
  }

  // ComputeCommandBuffer ---------------------------------------------------------------------------------------------

  std::vector<std::shared_ptr<ComputeCommandBuffer>> allocateComputeCommandBuffers(
      Device const& device, CommandBufferCreateFlags const&, utils::SizeT count)
  {
    return allocateBaseCommandBuffers<ComputeCommandBuffer, ComputeCommandBufferImpl>(
        device, device.getImpl()->getQueues().computeQueue, count);
  }

  std::shared_ptr<ComputeCommandBuffer> allocateComputeCommandBuffer(
      Device const& device, CommandBufferCreateFlags const& createFlags)
  {
    return allocateComputeCommandBuffers(device, createFlags, 1).front();
  }

  std::vector<Semaphore> submitCommandBuffers(
      std::vector<std::pair<std::shared_ptr<ComputeCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos)
  {
    auto device = implCast<BaseCommandBufferImpl>(submitInfos.front().first)->getDeice().getImpl();

    return submitBaseCommandBuffers(device->getVkDevice(), device->getQueues().computeQueue, submitInfos);
  }

  Semaphore submitCommandBuffer(
      std::shared_ptr<ComputeCommandBuffer> const& commandBuffer, std::vector<WaitInfo> const& waitInfos)
  {
    return submitCommandBuffers(std::vector{std::pair{commandBuffer, waitInfos}}).front();
  }

  // GraphicCommandBuffer ---------------------------------------------------------------------------------------------

  std::vector<std::shared_ptr<GraphicCommandBuffer>> allocateGraphicCommandBuffers(
      Device const& device, CommandBufferCreateFlags const&, utils::SizeT count)
  {
    return allocateBaseCommandBuffers<GraphicCommandBuffer, GraphicCommandBufferImpl>(
        device, device.getImpl()->getQueues().graphicQueue, count);
  }

  std::shared_ptr<GraphicCommandBuffer> allocateGraphicCommandBuffer(
      Device const& device, CommandBufferCreateFlags const& createFlags)
  {
    return allocateGraphicCommandBuffers(device, createFlags, 1).front();
  }

  std::vector<Semaphore> submitCommandBuffers(
      std::vector<std::pair<std::shared_ptr<GraphicCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos)
  {
    auto device = implCast<BaseCommandBufferImpl>(submitInfos.front().first)->getDeice().getImpl();

    return submitBaseCommandBuffers(device->getVkDevice(), device->getQueues().graphicQueue, submitInfos);
  }

  Semaphore submitCommandBuffer(
      std::shared_ptr<GraphicCommandBuffer> const& commandBuffer, std::vector<WaitInfo> const& waitInfos)
  {
    return submitCommandBuffers(std::vector{std::pair{commandBuffer, waitInfos}}).front();
  }

  // GraphicCommandBuffer ---------------------------------------------------------------------------------------------

}  // namespace vulkan