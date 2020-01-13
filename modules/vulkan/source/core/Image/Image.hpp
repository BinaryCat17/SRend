#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // ImageImpl --------------------------------------------------------------------------------------------------------

  class ImageImpl
  {
   public:
    virtual ~ImageImpl() = default;

    [[nodiscard]] virtual Device const& getDevice() const = 0;

    [[nodiscard]] virtual Format getFormat() const = 0;

    [[nodiscard]] virtual utils::Extent3D getExtent() const = 0;

    [[nodiscard]] virtual ImageSubResourceRange getRange() const = 0;

    [[nodiscard]] virtual SampleCountFlagBits getSampleCount() const = 0;

    [[nodiscard]] virtual vk::Image getVkImage() const = 0;

    [[nodiscard]] virtual vk::ImageView getVkImageView() const = 0;
  };

  // BaseImage --------------------------------------------------------------------------------------------------------

  class BaseImage : public ImageImpl
  {
   public:
    explicit BaseImage(std::shared_ptr<DeviceImpl> device, ImageCreateFlags const& createFlags, Format format,
        ImageUsageFlags const& usage, utils::Extent3D const& extent, utils::SizeT mipLevelsCount,
        utils::SizeT arrayLayersCount, SampleCountFlagBits sampleCount, MemoryType memoryType);

    BaseImage(BaseImage const&) = delete;

    BaseImage(BaseImage&&) = delete;

    BaseImage& operator=(BaseImage const&) = delete;

    BaseImage& operator=(BaseImage&&) = delete;

    ~BaseImage() override;

    [[nodiscard]] Device const& getDevice() const override
    {
      return device_;
    }

    [[nodiscard]] Format getFormat() const override
    {
      return format_;
    }

    [[nodiscard]] utils::Extent3D getExtent() const override
    {
      return extent_;
    }

    [[nodiscard]] ImageSubResourceRange getRange() const override
    {
      return ImageSubResourceRange(0, mipLevelsCount_, 0, arrayLayersCount_);
    }

    [[nodiscard]] SampleCountFlagBits getSampleCount() const override
    {
      return sampleCount_;
    }

    [[nodiscard]] vk::Image getVkImage() const override
    {
      return vkImage_;
    }

    [[nodiscard]] vk::ImageView getVkImageView() const override
    {
      return vkImageView_;
    }

   private:
    Device device_;
    utils::Extent3D extent_;
    Format format_;
    utils::SizeT mipLevelsCount_;
    utils::SizeT arrayLayersCount_;
    SampleCountFlagBits sampleCount_;
    vk::Image vkImage_;
    vk::ImageView vkImageView_;
  };

  // ViewImage --------------------------------------------------------------------------------------------------------

  class ViewImage : public ImageImpl
  {
   public:
    ViewImage(std::shared_ptr<DeviceImpl> device, Image image, ImageSubResourceRange range,
        std::optional<Format> const& formatView, ComponentMapping const& components);

    ViewImage(DeviceImpl const&) = delete;

    ViewImage(ViewImage&&) = delete;

    ViewImage& operator=(ViewImage const&) = delete;

    ViewImage& operator=(ViewImage&&) = delete;

    ~ViewImage() override;

    [[nodiscard]] Device const& getDevice() const override
    {
      return device_;
    }

    [[nodiscard]] Format getFormat() const override
    {
      return format_;
    }

    [[nodiscard]] utils::Extent3D getExtent() const override
    {
      return image_.getExtent();
    }

    [[nodiscard]] ImageSubResourceRange getRange() const override;

    [[nodiscard]] SampleCountFlagBits getSampleCount() const override
    {
      return image_.getSampleCount();
    }

    [[nodiscard]] vk::Image getVkImage() const override
    {
      return image_.getImpl()->getVkImage();
    }

    [[nodiscard]] vk::ImageView getVkImageView() const override
    {
      return vkImageView_;
    }

   private:
    Device device_;
    ImageSubResourceRange range_;
    Image image_;
    Format format_;
    vk::ImageView vkImageView_;
  };

}  // namespace vulkan