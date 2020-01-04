#include "ImageImpl.hpp"

namespace vulkan
{
  // TextureImage -----------------------------------------------------------------------------------------------------

  std::shared_ptr<TextureImage> createTextureImage(Device const& device, ImageCreateFlags const& createFlags,
      utils::Extent3D const& extent, ImageFormat format, utils::SizeT mipLevelCount, utils::SizeT arrayLayersCount,
      SampleCount sampleCount)
  {
    return std::make_shared<TextureImageImpl>(device, createFlags, extent, format, mipLevelCount, arrayLayersCount,
        sampleCount, vk::ImageUsageFlagBits::eSampled);
  }

  std::shared_ptr<TextureImage> createTextureImage(Device const& device, std::shared_ptr<TextureImage> const& image,
      ImageSubResourceRange const& range, ComponentMapping const& components)
  {
    return std::make_shared<TextureImageViewImpl>(device, image, range, components);
  }

  // ColorAttachmentImage ---------------------------------------------------------------------------------------------

  std::shared_ptr<ColorAttachmentImage> createColorAttachmentImage(Device const& device,
      ImageCreateFlags const& createFlags, utils::Extent3D const& extent, ImageFormat format,
      utils::SizeT mipLevelCount, utils::SizeT arrayLayersCount, SampleCount sampleCount)
  {
    return std::make_shared<ColorAttachmentImageImpl>(device, createFlags, extent, format, mipLevelCount,
        arrayLayersCount, sampleCount, vk::ImageUsageFlagBits::eColorAttachment);
  }

  std::shared_ptr<ColorAttachmentImage> createColorAttachmentImage(Device const& device,
      std::shared_ptr<TextureImage> const& image, ImageSubResourceRange const& range,
      ComponentMapping const& components)
  {
    return std::make_shared<ColorAttachmentImageViewImpl>(device, image, range, components);
  }

  // DepthAttachmentImage ---------------------------------------------------------------------------------------------

  std::shared_ptr<ColorAttachmentImage> createDepthAttachmentImagee(Device const& device,
      ImageCreateFlags const& createFlags, utils::Extent3D const& extent, ImageFormat format,
      utils::SizeT mipLevelCount, utils::SizeT arrayLayersCount, SampleCount sampleCount)
  {
    return std::make_shared<DepthAttachmentImageImpl>(device, createFlags, extent, format, mipLevelCount,
        arrayLayersCount, sampleCount, vk::ImageUsageFlagBits::eColorAttachment);
  }

  std::shared_ptr<ColorAttachmentImage> createDepthAttachmentImage(Device const& device,
      std::shared_ptr<TextureImage> const& image, ImageSubResourceRange const& range,
      ComponentMapping const& components)
  {
    return std::make_shared<DepthAttachmentImageViewImpl>(device, image, range, components);
  }

}  // namespace vulkan