#include "swapchain_t.hpp"

namespace vulkan
{
  // helpers ----------------------------------------------------------------------------------------------

  std::vector<VkPipelineStageFlags> to_vk_stages(std::vector<wait_info> const& wait_infos)
  {
    std::vector<VkPipelineStageFlags> result;
    for (auto const& wait_info : wait_infos)
    {
      result.push_back(static_cast<VkPipelineStageFlags>(wait_info.wait_stages));
    }
    return result;
  }

  // swapchain --------------------------------------------------------------------------------------------

  swapchain create_swapchain(device device, surface surface, vk::SurfaceFormatKHR format)
  {
    return std::make_shared<swapchain_t>(device, surface, format);
  }

  vk::SurfaceFormatKHR get_format(swapchain swapchain)
  {
    return swapchain->get_format();
  }

  vk::Semaphore present(swapchain swapchain, queue queue, image image, std::vector<wait_info> const& wait_infos)
  {
    std::vector<VkSemaphore> wait_semaphores = to_vk_semaphores(wait_infos);
    std::vector<VkPipelineStageFlags> wait_stages = to_vk_stages(wait_infos);
    VezSwapchain vk_swapchain = swapchain->get_vk_swapchain();
    VkImage vk_image = image->get_vk_image();
    VkSemaphore signal_semaphore = nullptr;

    VezPresentInfo present_info = {};
    present_info.swapchainCount = 1;
    present_info.pSwapchains = &vk_swapchain;
    present_info.pImages = &vk_image;
    present_info.waitSemaphoreCount = static_cast<uint32_t>(wait_semaphores.size());
    present_info.pWaitSemaphores = wait_semaphores.data();
    present_info.pWaitDstStageMask = wait_stages.data();
    present_info.signalSemaphoreCount = 1;
    present_info.pSignalSemaphores = &signal_semaphore;

    vezQueuePresent(queue->get_vk_queue(), &present_info);

    return signal_semaphore;
  }
}  // namespace vulkan