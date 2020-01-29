#include "Image.hpp"
#include "../../../include/vulkan/core.hpp"

namespace vulkan
{
  // utils  -----------------------------------------------------------------------------------------------------------

  VkImageCreateFlags toVkImageCreateFlags(ImageCreateFlags const& createFlags)
  {
    return static_cast<VkImageCreateFlags>(createFlags);
  }

  VkImageUsageFlags toVkImageUsage(ImageUsageFlags usage)
  {
    return static_cast<VkImageUsageFlags>(usage);
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

  VkImageType pickVkImageType(utils::Extent3D const& extent)
  {
    if (extent.height() == 1)
    {
      return VK_IMAGE_TYPE_1D;
    }
    else if (extent.depth() == 1)
    {
      return VK_IMAGE_TYPE_2D;
    }
    else
    {
      return VK_IMAGE_TYPE_3D;
    }
  }

  VkImageViewType pickVkImageViewType(VkImageType type, ImageSubResourceRange const& range)
  {
    switch (type)
    {
      case VK_IMAGE_TYPE_1D:
        if (range.arrayLayerCount > 1)
        {
          return VK_IMAGE_VIEW_TYPE_1D_ARRAY;
        }
        return VK_IMAGE_VIEW_TYPE_1D;
      case VK_IMAGE_TYPE_2D:
        if (range.arrayLayerCount > 1)
        {
          return VK_IMAGE_VIEW_TYPE_2D_ARRAY;
        }
        return VK_IMAGE_VIEW_TYPE_2D;
      case VK_IMAGE_TYPE_3D:
        if (range.arrayLayerCount > 1)
        {
          throw std::runtime_error("3D image array not supported");
        }
        return VK_IMAGE_VIEW_TYPE_3D;
      default:
        throw std::runtime_error("undefined image view type");
    }
  }

  vk::Image createVkImage(Device const& device, ImageCreateFlags const& createFlags, Format format,
      ImageUsageFlags const& usage, utils::Extent3D const& extent, utils::SizeT mipLevelsCount,
      utils::SizeT arrayLayersCount, SampleCountFlagBits sampleCount, MemoryType memoryType, VkImageType type)
  {
    VezImageCreateInfo createInfo = {};
    createInfo.flags = toVkImageCreateFlags(createFlags);
    createInfo.usage = toVkImageUsage(usage) | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    createInfo.format = toVkFormat(format);
    createInfo.extent = toVkExtent(extent);
    createInfo.arrayLayers = static_cast<uint32_t>(arrayLayersCount);
    createInfo.mipLevels = static_cast<uint32_t>(mipLevelsCount);
    createInfo.samples = toVkSampleCount(sampleCount);
    createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    createInfo.imageType = type;

    VkImage result = nullptr;
    checkResult(vezCreateImage(device.getImpl()->getVkDevice(), toVkMemoryFlags(memoryType), &createInfo, &result));
    return result;
  }

  vk::ImageView createVkImageView(Device const& device, vk::Image image, Format format, VkImageType type,
      ImageSubResourceRange const& range, ComponentMapping const& components)
  {
    VezImageViewCreateInfo createInfo = {};
    createInfo.image = image;
    createInfo.format = toVkFormat(format);
    createInfo.components = toVkComponentMapping(components);
    createInfo.subresourceRange = toVkImageSubResourceRange(range);
    createInfo.viewType = pickVkImageViewType(type, range);

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
    VkImageType imageType = pickVkImageType(extent);

    vkImage_ = createVkImage(device_, createFlags, format, usage, extent, mipLevelsCount, arrayLayersCount, sampleCount,
        memoryType, imageType);
    vkImageView_ = createVkImageView(device_, vkImage_, format, imageType,
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
        vkImageView_(createVkImageView(
            device_, image_.getImpl()->getVkImage(), format_, pickVkImageType(image_.getExtent()), range, components))
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

  Image::Image(Device const& device, ImageCreateFlags const& createFlags, utils::Extent3D const& extent, Format format,
      ImageUsageFlags const& usage, utils::SizeT mipLevelsCount, utils::SizeT arrayLayersCount,
      SampleCountFlagBits sampleCount, MemoryType memoryType)
      : pimpl_(std::make_shared<BaseImage>(device.getImpl(), createFlags, format, usage, extent, mipLevelsCount,
            arrayLayersCount, sampleCount, memoryType))
  {
  }

  Image::Image(Device const& device, Image const& image, ImageSubResourceRange const& range,
      std::optional<Format> const& formatView, ComponentMapping const& components)
      : pimpl_(std::make_shared<ViewImage>(device.getImpl(), image, range, formatView, components))
  {
  }

  [[nodiscard]] Format Image::getFormat() const noexcept
  {
    return pimpl_->getFormat();
  }

  [[nodiscard]] utils::Extent3D Image::getExtent() const noexcept
  {
    return pimpl_->getExtent();
  }

  [[nodiscard]] ImageSubResourceRange Image::getSubResourceRange() const noexcept
  {
    return pimpl_->getRange();
  }

  [[nodiscard]] SampleCountFlagBits Image::getSampleCount() const noexcept
  {
    return pimpl_->getSampleCount();
  }

}  // namespace vulkan