#include "Image.hpp"

namespace vulkan
{
  // utils  -----------------------------------------------------------------------------------------------------------

  vk::ImageCreateFlags toVkImageCreateFlags(ImageCreateFlags const& createFlags)
  {
    return vk::ImageCreateFlags(static_cast<VkImageCreateFlags>(createFlags));
  }

  vk::ImageUsageFlags toVkImageUsage(ImageUsageFlags usage)
  {
    return vk::ImageUsageFlags(static_cast<VkImageUsageFlags>(usage));
  }

  vk::ComponentSwizzle toVkComponentSwizzle(ComponentSwizzle component)
  {
    return static_cast<vk::ComponentSwizzle>(component);
  }

  vk::ComponentMapping toVkComponentMapping(ComponentMapping const& components)
  {
    return vk::ComponentMapping(toVkComponentSwizzle(components.r), toVkComponentSwizzle(components.g),
        toVkComponentSwizzle(components.b), toVkComponentSwizzle(components.a));
  }

  VezImageSubresourceRange toVkImageSubResourceRange(ImageSubResourceRange const& range)
  {
    VezImageSubresourceRange result = {};
    result.baseArrayLayer = static_cast<uint32_t>(range.baseArrayLayer);
    result.baseMipLevel = static_cast<uint32_t>(range.baseMipLevel);
    result.layerCount = static_cast<uint32_t>(range.arrayLayerCount);
    result.levelCount = static_cast<uint32_t>(range.mipLevelCount);

    return result;
  }

  vk::AttachmentLoadOp toVkAttachmentLoadOp(AttachmentLoadOp op)
  {
    return static_cast<vk::AttachmentLoadOp>(op);
  }

  vk::AttachmentStoreOp toVkAttachmentStoreOp(AttachmentStoreOp op)
  {
    return static_cast<vk::AttachmentStoreOp>(op);
  }

  vk::ImageType pickVkImageType(utils::Extent3D const& extent)
  {
    if (extent.height() == 1)
    {
      return vk::ImageType::e1D;
    }
    else if (extent.depth() == 1)
    {
      return vk::ImageType::e2D;
    }
    else
    {
      return vk::ImageType::e3D;
    }
  }

  vk::ImageViewType pickVkImageViewType(vk::ImageType type, ImageSubResourceRange const& range)
  {
    switch (type)
    {
      case vk::ImageType::e1D:
        if (range.arrayLayerCount > 1)
        {
          return vk::ImageViewType::e1DArray;
        }
        return vk::ImageViewType::e1D;
      case vk::ImageType::e2D:
        if (range.arrayLayerCount > 1)
        {
          return vk::ImageViewType::e2DArray;
        }
        return vk::ImageViewType::e2D;
      case vk::ImageType::e3D:
        if (range.arrayLayerCount > 1)
        {
          throw std::runtime_error("3D image array not supported");
        }
        return vk::ImageViewType::e3D;
    }
    throw std::runtime_error("undefined image view type");
  }

  vk::Image createVkImage(Device const& device, ImageCreateFlags const& createFlags, vk::Format format,
      ImageUsageFlags const& usage, utils::Extent3D const& extent, utils::SizeT mipLevelsCount,
      utils::SizeT arrayLayersCount, SampleCountFlagBits sampleCount, MemoryType memoryType, vk::ImageType type)
  {
    VezImageCreateInfo createInfo = {};
    createInfo.flags = static_cast<VkImageCreateFlags>(toVkImageCreateFlags(createFlags));
    createInfo.usage = static_cast<VkImageUsageFlags>(
        toVkImageUsage(usage) | vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst);
    createInfo.format = static_cast<VkFormat>(format);
    createInfo.extent = toVkExtent(extent);
    createInfo.arrayLayers = static_cast<uint32_t>(arrayLayersCount);
    createInfo.mipLevels = static_cast<uint32_t>(mipLevelsCount);
    createInfo.samples = static_cast<VkSampleCountFlagBits>(toVkSampleCount(sampleCount));
    createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    createInfo.imageType = static_cast<VkImageType>(type);

    VkImage result = nullptr;
    checkResult(vezCreateImage(device.getImpl()->getVkDevice(), toVkMemoryFlags(memoryType), &createInfo, &result));
    return result;
  }

  vk::ImageView createVkImageView(Device const& device, vk::Image image, vk::Format format, vk::ImageType type,
      ImageSubResourceRange const& range, ComponentMapping const& components)
  {
    VezImageViewCreateInfo createInfo = {};
    createInfo.image = image;
    createInfo.format = static_cast<VkFormat>(format);
    createInfo.components = toVkComponentMapping(components);
    createInfo.subresourceRange = toVkImageSubResourceRange(range);
    createInfo.viewType = static_cast<VkImageViewType>(pickVkImageViewType(type, range));

    VkImageView result = nullptr;
    checkResult(vezCreateImageView(device.getImpl()->getVkDevice(), &createInfo, &result));

    return result;
  }

  // BaseImage --------------------------------------------------------------------------------------------------------

  BaseImage::BaseImage(std::shared_ptr<DeviceImpl> device, ImageCreateFlags const& createFlags, Format format,
      ImageUsageFlags const& usage, utils::Extent3D const& extent, utils::SizeT mipLevelsCount,
      utils::SizeT arrayLayersCount, SampleCountFlagBits sampleCount, MemoryType memoryType)
      : device_(std::move(device)),
        extent_(extent),
        format_(format),
        mipLevelsCount_(mipLevelsCount),
        arrayLayersCount_(arrayLayersCount),
        sampleCount_(sampleCount)
  {
    vk::Format vkImageFormat = toVkFormat(format);
    vk::ImageType vkImageType = pickVkImageType(extent);

    vkImage_ = createVkImage(device_, createFlags, vkImageFormat, usage, extent, mipLevelsCount, arrayLayersCount,
        sampleCount, memoryType, vkImageType);
    vkImageView_ = createVkImageView(device_, vkImage_, vkImageFormat, vkImageType,
        ImageSubResourceRange(0, mipLevelsCount_, 0, arrayLayersCount_), ComponentMapping());
  }

  BaseImage::~BaseImage()
  {
    vezDestroyImageView(device_.getImpl()->getVkDevice(), vkImageView_);
    vezDestroyImage(device_.getImpl()->getVkDevice(), vkImage_);
  }

  // ViewImage --------------------------------------------------------------------------------------------------------

  ViewImage::ViewImage(std::shared_ptr<DeviceImpl> device, Image image, ImageSubResourceRange range,
      std::optional<Format> const& formatView, ComponentMapping const& components)
      : device_(std::move(device)),
        range_(range),
        image_(std::move(image)),
        format_(formatView ? *formatView : image_.getFormat()),
        vkImageView_(createVkImageView(device_, image_.getImpl()->getVkImage(), toVkFormat(format_),
            pickVkImageType(image_.getExtent()), range, components))
  {
  }

  ViewImage::~ViewImage()
  {
    vezDestroyImageView(device_.getImpl()->getVkDevice(), vkImageView_);
  }

  ImageSubResourceRange ViewImage::getRange() const
  {
    auto imageRange = image_.getSubResourceRange();

    return ImageSubResourceRange(range_.baseMipLevel + imageRange.baseMipLevel, range_.mipLevelCount,
        range_.baseArrayLayer + imageRange.baseArrayLayer, range_.arrayLayerCount);
  }

  // Image ------------------------------------------------------------------------------------------------------------

  [[nodiscard]] Format Image::getFormat() const
  {
    return pimpl_->getFormat();
  }

  [[nodiscard]] utils::Extent3D Image::getExtent() const
  {
    return pimpl_->getExtent();
  }

  [[nodiscard]] ImageSubResourceRange Image::getSubResourceRange() const
  {
    return pimpl_->getRange();
  }

  [[nodiscard]] SampleCountFlagBits Image::getSampleCount() const
  {
    return pimpl_->getSampleCount();
  }

}  // namespace vulkan