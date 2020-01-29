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
      std::shared_ptr<DeviceImpl> device, FramebufferCreateFlags const&)
      : device_(std::move(device))
  {
  }

  void FramebufferImpl::addAttachment(Image const& image)
  {
    images_.push_back(image);
    needUpdate_ = true;
  }

  void FramebufferImpl::setAttachment(utils::IndexT index, Image const& image)
  {
    images_[index] = image;
    needUpdate_ = true;
  }

  void FramebufferImpl::update()
  {
    if (needUpdate_)
    {
      vkFramebuffer_ = createVkFramebuffer(device_, images_);
      needUpdate_ = false;
    }
  }

  // Framebuffer ------------------------------------------------------------------------------------------------------

  Framebuffer::Framebuffer(Device const& device, FramebufferCreateFlags const& createFlags)
      : pimpl_(std::make_shared<FramebufferImpl>(device.getImpl(), createFlags))
  {
  }

  void Framebuffer::addAttachment(Image const& image)
  {
    pimpl_->addAttachment(image);
  }

  void Framebuffer::setAttachment(utils::IndexT index, Image const& image)
  {
    pimpl_->setAttachment(index, image);
  }

  void Framebuffer::removeAttachment(utils::IndexT index)
  {
    pimpl_->removeAttachment(index);
  }

}  // namespace vulkan