#include "ImageImpl.hpp"

namespace vulkan
{
  // utils  -----------------------------------------------------------------------------------------------------------

  vk::ImageCreateFlags toVkImageCreateFlags(ImageCreateFlags const&)
  {
    return {};
  }

  vk::Format toVkFormat(ImageFormat format)
  {
    switch (format)
    {
      case ImageFormat::Undefined:
        return vk::Format::eUndefined;
      case ImageFormat::R8Unorm:
        return vk::Format::eR8Unorm;
      case ImageFormat::R8Snorm:
        return vk::Format::eR8Snorm;
      case ImageFormat::R8Uscaled:
        return vk::Format::eR8Uscaled;
      case ImageFormat::R8Sscaled:
        return vk::Format::eR8Sscaled;
      case ImageFormat::R8Uint:
        return vk::Format::eR8Uint;
      case ImageFormat::R8Sint:
        return vk::Format::eR8Sint;
      case ImageFormat::R8Srgb:
        return vk::Format::eR8Srgb;
      case ImageFormat::R8G8Unorm:
        return vk::Format::eR8G8Unorm;
      case ImageFormat::R8G8Snorm:
        return vk::Format::eR8G8Snorm;
      case ImageFormat::R8G8Uscaled:
        return vk::Format::eR8G8Uscaled;
      case ImageFormat::R8G8Sscaled:
        return vk::Format::eR8G8Sscaled;
      case ImageFormat::R8G8Uint:
        return vk::Format::eR8G8Uint;
      case ImageFormat::R8G8Sint:
        return vk::Format::eR8G8Sint;
      case ImageFormat::R8G8Srgb:
        return vk::Format::eR8G8Srgb;
      case ImageFormat::R8G8B8Unorm:
        return vk::Format::eR8G8B8Unorm;
      case ImageFormat::R8G8B8Snorm:
        return vk::Format::eR8G8B8Snorm;
      case ImageFormat::R8G8B8Uscaled:
        return vk::Format::eR8G8B8Uscaled;
      case ImageFormat::R8G8B8Sscaled:
        return vk::Format::eR8G8B8Sscaled;
      case ImageFormat::R8G8B8Uint:
        return vk::Format::eR8G8B8Uint;
      case ImageFormat::R8G8B8Sint:
        return vk::Format::eR8G8B8Sint;
      case ImageFormat::R8G8B8Srgb:
        return vk::Format::eR8G8B8Srgb;
      case ImageFormat::B8G8R8Unorm:
        return vk::Format::eB8G8R8Unorm;
      case ImageFormat::B8G8R8Snorm:
        return vk::Format::eB8G8R8Snorm;
      case ImageFormat::B8G8R8Uscaled:
        return vk::Format::eB8G8R8Uscaled;
      case ImageFormat::B8G8R8Sscaled:
        return vk::Format::eB8G8R8Sscaled;
      case ImageFormat::B8G8R8Uint:
        return vk::Format::eB8G8R8Uint;
      case ImageFormat::B8G8R8Sint:
        return vk::Format::eB8G8R8Sint;
      case ImageFormat::B8G8R8Srgb:
        return vk::Format::eB8G8R8Srgb;
      case ImageFormat::R8G8B8A8Unorm:
        return vk::Format::eR8G8B8A8Unorm;
      case ImageFormat::R8G8B8A8Snorm:
        return vk::Format::eR8G8B8A8Snorm;
      case ImageFormat::R8G8B8A8Uscaled:
        return vk::Format::eR8G8B8A8Uscaled;
      case ImageFormat::R8G8B8A8Sscaled:
        return vk::Format::eR8G8B8A8Sscaled;
      case ImageFormat::R8G8B8A8Uint:
        return vk::Format::eR8G8B8A8Uint;
      case ImageFormat::R8G8B8A8Sint:
        return vk::Format::eR8G8B8A8Sint;
      case ImageFormat::R8G8B8A8Srgb:
        return vk::Format::eR8G8B8A8Srgb;
      case ImageFormat::B8G8R8A8Unorm:
        return vk::Format::eB8G8R8A8Unorm;
      case ImageFormat::B8G8R8A8Snorm:
        return vk::Format::eB8G8R8A8Snorm;
      case ImageFormat::B8G8R8A8Uscaled:
        return vk::Format::eB8G8R8A8Uscaled;
      case ImageFormat::B8G8R8A8Sscaled:
        return vk::Format::eB8G8R8A8Sscaled;
      case ImageFormat::B8G8R8A8Uint:
        return vk::Format::eB8G8R8A8Uint;
      case ImageFormat::B8G8R8A8Sint:
        return vk::Format::eB8G8R8A8Sint;
      case ImageFormat::B8G8R8A8Srgb:
        return vk::Format::eB8G8R8A8Srgb;
      case ImageFormat::R16Unorm:
        return vk::Format::eR16Unorm;
      case ImageFormat::R16Snorm:
        return vk::Format::eR16Snorm;
      case ImageFormat::R16Uscaled:
        return vk::Format::eR16Uscaled;
      case ImageFormat::R16Sscaled:
        return vk::Format::eR16Sscaled;
      case ImageFormat::R16Uint:
        return vk::Format::eR16Uint;
      case ImageFormat::R16Sint:
        return vk::Format::eR16Sint;
      case ImageFormat::R16Sfloat:
        return vk::Format::eR16Sfloat;
      case ImageFormat::R16G16Unorm:
        return vk::Format::eR16G16Unorm;
      case ImageFormat::R16G16Snorm:
        return vk::Format::eR16G16Snorm;
      case ImageFormat::R16G16Uscaled:
        return vk::Format::eR16G16Uscaled;
      case ImageFormat::R16G16Sscaled:
        return vk::Format::eR16G16Sscaled;
      case ImageFormat::R16G16Uint:
        return vk::Format::eR16G16Uint;
      case ImageFormat::R16G16Sint:
        return vk::Format::eR16G16Sint;
      case ImageFormat::R16G16Sfloat:
        return vk::Format::eR16G16Sfloat;
      case ImageFormat::R16G16B16Unorm:
        return vk::Format::eR16G16B16Unorm;
      case ImageFormat::R16G16B16Snorm:
        return vk::Format::eR16G16B16Snorm;
      case ImageFormat::R16G16B16Uscaled:
        return vk::Format::eR16G16B16Uscaled;
      case ImageFormat::R16G16B16Sscaled:
        return vk::Format::eR16G16B16Sscaled;
      case ImageFormat::R16G16B16Uint:
        return vk::Format::eR16G16B16Uint;
      case ImageFormat::R16G16B16Sint:
        return vk::Format::eR16G16B16Sint;
      case ImageFormat::R16G16B16Sfloat:
        return vk::Format::eR16G16B16Sfloat;
      case ImageFormat::R16G16B16A16Unorm:
        return vk::Format::eR16G16B16A16Unorm;
      case ImageFormat::R16G16B16A16Snorm:
        return vk::Format::eR16G16B16A16Snorm;
      case ImageFormat::R16G16B16A16Uscaled:
        return vk::Format::eR16G16B16A16Uscaled;
      case ImageFormat::R16G16B16A16Sscaled:
        return vk::Format::eR16G16B16A16Sscaled;
      case ImageFormat::R16G16B16A16Uint:
        return vk::Format::eR16G16B16A16Uint;
      case ImageFormat::R16G16B16A16Sint:
        return vk::Format::eR16G16B16A16Sint;
      case ImageFormat::R16G16B16A16Sfloat:
        return vk::Format::eR16G16B16A16Sfloat;
      case ImageFormat::R32Uint:
        return vk::Format::eR32Uint;
      case ImageFormat::R32Sint:
        return vk::Format::eR32Sint;
      case ImageFormat::R32Sfloat:
        return vk::Format::eR32Sfloat;
      case ImageFormat::R32G32Uint:
        return vk::Format::eR32G32Uint;
      case ImageFormat::R32G32Sint:
        return vk::Format::eR32G32Sint;
      case ImageFormat::R32G32Sfloat:
        return vk::Format::eR32G32Sfloat;
      case ImageFormat::R32G32B32Uint:
        return vk::Format::eR32G32B32Uint;
      case ImageFormat::R32G32B32Sint:
        return vk::Format::eR32G32B32Sint;
      case ImageFormat::R32G32B32Sfloat:
        return vk::Format::eR32G32B32Sfloat;
      case ImageFormat::R32G32B32A32Uint:
        return vk::Format::eR32G32B32A32Uint;
      case ImageFormat::R32G32B32A32Sint:
        return vk::Format::eR32G32B32A32Sint;
      case ImageFormat::R32G32B32A32Sfloat:
        return vk::Format::eR32G32B32A32Sfloat;
      case ImageFormat::R64Uint:
        return vk::Format::eR64Uint;
      case ImageFormat::R64Sint:
        return vk::Format::eR64Sint;
      case ImageFormat::R64Sfloat:
        return vk::Format::eR64Sfloat;
      case ImageFormat::R64G64Uint:
        return vk::Format::eR64G64Uint;
      case ImageFormat::R64G64Sint:
        return vk::Format::eR64G64Sint;
      case ImageFormat::R64G64Sfloat:
        return vk::Format::eR64G64Sfloat;
      case ImageFormat::R64G64B64Uint:
        return vk::Format::eR64G64B64Uint;
      case ImageFormat::R64G64B64Sint:
        return vk::Format::eR64G64B64Sint;
      case ImageFormat::R64G64B64Sfloat:
        return vk::Format::eR64G64B64Sfloat;
      case ImageFormat::R64G64B64A64Uint:
        return vk::Format::eR64G64B64A64Uint;
      case ImageFormat::R64G64B64A64Sint:
        return vk::Format::eR64G64B64A64Sint;
      case ImageFormat::R64G64B64A64Sfloat:
        return vk::Format::eR64G64B64A64Sfloat;
      case ImageFormat::D16Unorm:
        return vk::Format::eD16Unorm;
      case ImageFormat::D32Sfloat:
        return vk::Format::eD32Sfloat;
      case ImageFormat::S8Uint:
        return vk::Format::eS8Uint;
      case ImageFormat::D16UnormS8Uint:
        return vk::Format::eD16UnormS8Uint;
      case ImageFormat::D24UnormS8Uint:
        return vk::Format::eD24UnormS8Uint;
      case ImageFormat::D32SfloatS8Uint:
        return vk::Format::eD32SfloatS8Uint;
    }
  }

  vk::Extent3D toVkExtent(utils::Extent3D const& extent)
  {
    return VkExtent3D{extent.width(), extent.height(), extent.depth()};
  }

  vk::SampleCountFlagBits toVkSampleCount(SampleCount sampleCount)
  {
    switch (sampleCount)
    {
      case SampleCount::e1:
        return vk::SampleCountFlagBits::e1;
      case SampleCount::e2:
        return vk::SampleCountFlagBits::e2;
      case SampleCount::e4:
        return vk::SampleCountFlagBits::e4;
      case SampleCount::e8:
        return vk::SampleCountFlagBits::e8;
      case SampleCount::e16:
        return vk::SampleCountFlagBits::e16;
      case SampleCount::e32:
        return vk::SampleCountFlagBits::e32;
      case SampleCount::e64:
        return vk::SampleCountFlagBits::e64;
    }
  }

  vk::ComponentSwizzle toVkComponentSwizzle(ComponentSwizzle component)
  {
    switch (component)
    {
      case ComponentSwizzle::Identity:
        return vk::ComponentSwizzle::eIdentity;
      case ComponentSwizzle::Zero:
        return vk::ComponentSwizzle::eZero;
      case ComponentSwizzle::One:
        return vk::ComponentSwizzle::eOne;
      case ComponentSwizzle::R:
        return vk::ComponentSwizzle::eR;
      case ComponentSwizzle::G:
        return vk::ComponentSwizzle::eG;
      case ComponentSwizzle::B:
        return vk::ComponentSwizzle::eB;
      case ComponentSwizzle::A:
        return vk::ComponentSwizzle::eA;
    }
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
    switch (op)
    {
      case AttachmentLoadOp::Load:
        return vk::AttachmentLoadOp::eLoad;
      case AttachmentLoadOp::Clear:
        return vk::AttachmentLoadOp::eClear;
      case AttachmentLoadOp::DontCare:
        return vk::AttachmentLoadOp::eDontCare;
    }
  }

  vk::AttachmentStoreOp toVkAttachmentStoreOp(AttachmentStoreOp op)
  {
    switch (op)
    {
      case AttachmentStoreOp::Store:
        return vk::AttachmentStoreOp::eStore;
      case AttachmentStoreOp::DontCare:
        return vk::AttachmentStoreOp::eDontCare;
    }
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
  }

  vk::Image createVkImage(Device const& device, ImageCreateFlags const& createFlags, utils::Extent3D const& extent,
      utils::SizeT mipLevelCount, utils::SizeT arrayLayersCount, SampleCount sampleCount,
      vk::ImageUsageFlags const& usage, vk::ImageType type, vk::Format format)
  {
    VezImageCreateInfo createInfo = {};
    createInfo.flags = static_cast<VkImageCreateFlags>(toVkImageCreateFlags(createFlags));
    createInfo.usage = static_cast<VkImageUsageFlags>(usage);
    createInfo.format = static_cast<VkFormat>(format);
    createInfo.extent = toVkExtent(extent);
    createInfo.arrayLayers = arrayLayersCount;
    createInfo.mipLevels = mipLevelCount;
    createInfo.samples = static_cast<VkSampleCountFlagBits>(toVkSampleCount(sampleCount));
    createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    createInfo.imageType = static_cast<VkImageType>(type);

    VkImage result = nullptr;
    checkResult(vezCreateImage(device.getImpl()->getVkDevice(), VEZ_MEMORY_GPU_ONLY, &createInfo, &result));
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

  // ImageImpl ------------------------------------------------------------------------------------------------------

  BaseImageImpl::BaseImageImpl(Device device, ImageCreateFlags const& createFlags, utils::Extent3D const& extent,
      ImageFormat format, utils::SizeT mipLevelsCount, utils::SizeT arrayLayersCount, SampleCount sampleCount,
      vk::ImageUsageFlags const& usage)
      : device_(std::move(device)),
        extent_(extent),
        format_(format),
        mipLevelsCount_(mipLevelsCount),
        arrayLayersCount_(arrayLayersCount),
        sampleCount_(sampleCount)
  {
    vk::Format vkImageFormat = toVkFormat(format);
    vk::ImageType vkImageType = pickVkImageType(extent);

    vkImage_ = createVkImage(device_, createFlags, extent, mipLevelsCount, arrayLayersCount, sampleCount,
        usage | vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst, vkImageType,
        vkImageFormat);
    vkImageView_ = createVkImageView(device_, vkImage_, vkImageFormat, vkImageType,
        ImageSubResourceRange(0, mipLevelsCount_, 0, arrayLayersCount_), ComponentMapping());
  }

  BaseImageImpl::~BaseImageImpl()
  {
    vezDestroyImageView(device_.getImpl()->getVkDevice(), vkImageView_);
    vezDestroyImage(device_.getImpl()->getVkDevice(), vkImage_);
  }

  BaseImageViewImpl::BaseImageViewImpl(Device device, std::shared_ptr<TextureImage> const& image,
      ImageSubResourceRange const& range, ComponentMapping const& components)
      : device_(std::move(device)),
        range_(range),
        image_(implCast<BaseImage>(image)),
        vkImageView_(createVkImageView(device, image_->getVkImage(), toVkFormat(image_->getFormat()),
            pickVkImageType(image_->getExtent()), range, components))
  {
  }

  BaseImageViewImpl::~BaseImageViewImpl()
  {
    vezDestroyImageView(device_.getImpl()->getVkDevice(), vkImageView_);
  }

  ImageSubResourceRange BaseImageViewImpl::getRange() const
  {
    auto imageRange = image_->getRange();

    return ImageSubResourceRange(range_.baseMipLevel + imageRange.baseMipLevel, range_.mipLevelCount,
        range_.baseArrayLayer + imageRange.baseArrayLayer, range_.arrayLayerCount);
  }

  // ColorAttachmentImageImpl -----------------------------------------------------------------------------------------

  void BaseColorAttachmentImageImpl::setClearColor(std::array<float, 4> const& clearValue)
  {
    info_.clearValue.color = {{clearValue[0], clearValue[1], clearValue[2], clearValue[3]}};
  }

  void BaseColorAttachmentImageImpl::setLoadOp(AttachmentLoadOp op)
  {
    info_.loadOp = static_cast<VkAttachmentLoadOp>(toVkAttachmentLoadOp(op));
  }

  void BaseColorAttachmentImageImpl::setStoreOp(AttachmentStoreOp op)
  {
    info_.storeOp = static_cast<VkAttachmentStoreOp>(toVkAttachmentStoreOp(op));
  }

  // DepthAttachmentImageImpl -----------------------------------------------------------------------------------------

  void BaseDepthAttachmentImageImpl::setClearColor(float depth, unsigned stencil)
  {
    info_.clearValue.depthStencil = {depth, stencil};
  }

  void BaseDepthAttachmentImageImpl::setLoadOp(AttachmentLoadOp op)
  {
    info_.loadOp = static_cast<VkAttachmentLoadOp>(toVkAttachmentLoadOp(op));
  }

  void BaseDepthAttachmentImageImpl::setStoreOp(AttachmentStoreOp op)
  {
    info_.storeOp = static_cast<VkAttachmentStoreOp>(toVkAttachmentStoreOp(op));
  }

}  // namespace vulkan
