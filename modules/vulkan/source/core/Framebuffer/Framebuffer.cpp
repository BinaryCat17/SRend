#include "Framebuffer.hpp"
#include "../Image/Image.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  std::vector<VkImageView> toVkImageViews(std::vector<Image> const& images)
  {
    std::vector<VkImageView> result;
    for (auto const& image : images)
    {
      result.push_back(image.getImpl()->getVkImageView());
    }
    return result;
  }

  VezFramebuffer createVkFramebuffer(std::shared_ptr<DeviceImpl> const& device, std::vector<Image> const& images)
  {
    std::vector<VkImageView> imageViews = toVkImageViews(images);

    VezFramebufferCreateInfo createInfo = {};
    createInfo.pAttachments = imageViews.data();
    createInfo.attachmentCount = static_cast<uint32_t>(imageViews.size());

    auto extent = images.front().getExtent();
    createInfo.width = extent.width();
    createInfo.height = extent.height();
    createInfo.layers = extent.depth();

    VezFramebuffer result = nullptr;
    checkResult(vezCreateFramebuffer(device->getVkDevice(), &createInfo, &result));
    return result;
  }

  // FramebufferImpl --------------------------------------------------------------------------------------------------

  FramebufferImpl::FramebufferImpl(
      std::shared_ptr<DeviceImpl> device, FramebufferCreateFlags const&, std::vector<Image> const& images)
      : device_(std::move(device)), vkFramebuffer_(createVkFramebuffer(device_, images))
  {
  }

}  // namespace vulkan