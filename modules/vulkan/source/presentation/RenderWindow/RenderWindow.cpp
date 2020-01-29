#include "RenderWindow.hpp"
#include "../../core/Image/Image.hpp"
#include "../../core/PhysicalDevice/PhysicalDevice.hpp"
#include "../../core/Semaphore/Semaphore.hpp"


namespace vulkan::presentation
{
  // utils ------------------------------------------------------------------------------------------------------------

  VezSwapchain createVkSwapchain(
      std::shared_ptr<DeviceImpl> const& device, vk::SurfaceKHR vkSurface, Format format, ColorSpace colorSpace)
  {
    VezSwapchainCreateInfo create_info = {};
    create_info.format = {static_cast<VkFormat>(toVkFormat(format)), static_cast<VkColorSpaceKHR>(colorSpace)};
    create_info.surface = vkSurface;
    create_info.tripleBuffer = true;

    VezSwapchain swapchain_ = nullptr;
    checkResult(vezCreateSwapchain(device->getVkDevice(), &create_info, &swapchain_));
    return swapchain_;
  }

  std::vector<VkSemaphore> toVkSemaphores(std::vector<WaitInfo> const& waitInfos)
  {
    std::vector<VkSemaphore> result;
    for (auto const& waitInfo : waitInfos)
    {
      result.push_back(static_cast<VkSemaphore>(waitInfo.semaphore.getImpl()->getVkSemaphore()));
    }
    return result;
  }

  std::vector<VkPipelineStageFlags> toVkStages(std::vector<WaitInfo> const& waitInfos)
  {
    std::vector<VkPipelineStageFlags> result;
    for (auto const& waitInfo : waitInfos)
    {
      result.push_back(static_cast<VkPipelineStageFlags>(waitInfo.waitStages));
    }
    return result;
  }

  vk::Queue getPresentationQueue(std::shared_ptr<DeviceImpl> const& device, vk::SurfaceKHR vkSurface)
  {
    auto vkPhysicalDevice = device->getPhysicalDevice()->getVkPhysicalDevice();

    auto queueProperties = vkPhysicalDevice.getQueueFamilyProperties();

    for (utils::IndexT i = 0; i != queueProperties.size(); ++i)
    {
      VkBool32 supported = false;
      checkResult(vezGetPhysicalDevicePresentSupport(vkPhysicalDevice, static_cast<uint32_t>(i), vkSurface, &supported));

      if (supported)
      {
        VkQueue result = nullptr;
        vezGetDeviceQueue(device->getVkDevice(), static_cast<uint32_t>(i), 0, &result);
        return result;
      }
    }

    throw std::runtime_error("no presentation queue");
  }

  // RenderWindowImpl -------------------------------------------------------------------------------------------------

  RenderWindowImpl::RenderWindowImpl(std::shared_ptr<DeviceImpl> device, RenderWindowCreateFlags const&,
      wsystem::Window const& window, Format format, ColorSpace colorSpace)
      : device_(std::move(device)),
        vkSurface_(wsystem::createVulkanSurface(window, device_->getApplication()->getVkInstance())),
        vkPresentationQueue_(getPresentationQueue(device_, vkSurface_)),
        vkSwapchain_(createVkSwapchain(device_, vkSurface_, format, colorSpace))
  {
  }

  RenderWindowImpl::~RenderWindowImpl()
  {
    vezDestroySwapchain(device_->getVkDevice(), vkSwapchain_);
    device_->getApplication()->getVkInstance().destroySurfaceKHR(vkSurface_);
  }

  Semaphore RenderWindowImpl::present(Image const& image, std::vector<WaitInfo> const& waitInfo)
  {
    std::vector<VkSemaphore> wait_semaphores = toVkSemaphores(waitInfo);
    std::vector<VkPipelineStageFlags> wait_stages = toVkStages(waitInfo);
    VezSwapchain vk_swapchain = vkSwapchain_;
    VkImage vk_image = image.getImpl()->getVkImage();
    VkSemaphore signalSemaphore = nullptr;

    VezPresentInfo present_info = {};
    present_info.swapchainCount = 1;
    present_info.pSwapchains = &vk_swapchain;
    present_info.pImages = &vk_image;
    present_info.waitSemaphoreCount = static_cast<uint32_t>(wait_semaphores.size());
    present_info.pWaitSemaphores = wait_semaphores.data();
    present_info.pWaitDstStageMask = wait_stages.data();
    present_info.signalSemaphoreCount = 1;
    present_info.pSignalSemaphores = &signalSemaphore;

    vezQueuePresent(vkPresentationQueue_, &present_info);

    return Semaphore(std::make_shared<SemaphoreImpl>(signalSemaphore));
  }

  // RenderWindow -----------------------------------------------------------------------------------------------------

  Semaphore RenderWindow::present(Image const& image, std::vector<WaitInfo> const& waitInfo)
  {
    return pimpl_->present(image, waitInfo);
  }

}  // namespace vulkan