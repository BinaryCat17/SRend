#pragma once
#include "../Device/DeviceImpl.hpp"
#include "../Sampler/SamplerImpl.hpp"
#include "Image.hpp"

namespace vulkan
{
  // ImageImpl --------------------------------------------------------------------------------------------------------

  class BaseImage : public Image
  {
   public:
    [[nodiscard]] virtual Device const& getDevice() const = 0;

    [[nodiscard]] virtual vk::Image getVkImage() const = 0;

    [[nodiscard]] virtual vk::ImageView getVkImageView() const = 0;
  };

  class BaseImageImpl : public BaseImage
  {
   public:
    BaseImageImpl(Device device, ImageCreateFlags const& createFlags, utils::Extent3D const& extent, ImageFormat format,
        utils::SizeT mipLevelsCount, utils::SizeT arrayLayersCount, SampleCount sampleCount,
        vk::ImageUsageFlags const& usage);

    ~BaseImageImpl() override;

    [[nodiscard]] Device const& getDevice() const override
    {
      return device_;
    }

    [[nodiscard]] ImageFormat getFormat() const override
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

    [[nodiscard]] SampleCount getSampleCount() const override
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
    ImageFormat format_;
    utils::SizeT mipLevelsCount_;
    utils::SizeT arrayLayersCount_;
    SampleCount sampleCount_;
    vk::Image vkImage_;
    vk::ImageView vkImageView_;
  };

  class BaseImageViewImpl : public BaseImage
  {
   public:
    BaseImageViewImpl(Device device, std::shared_ptr<TextureImage> const& image, ImageSubResourceRange const& range,
        ComponentMapping const& components);

    ~BaseImageViewImpl() override;

    [[nodiscard]] Device const& getDevice() const override
    {
      return device_;
    }

    [[nodiscard]] ImageFormat getFormat() const override
    {
      return image_->getFormat();
    }

    [[nodiscard]] utils::Extent3D getExtent() const override
    {
      return image_->getExtent();
    }

    [[nodiscard]] ImageSubResourceRange getRange() const override;

    [[nodiscard]] SampleCount getSampleCount() const override
    {
      return image_->getSampleCount();
    }

    [[nodiscard]] vk::Image getVkImage() const override
    {
      return image_->getVkImage();
    }

    [[nodiscard]] vk::ImageView getVkImageView() const override
    {
      return vkImageView_;
    }

   private:
    Device device_;
    ImageSubResourceRange range_;
    std::shared_ptr<BaseImage> image_;
    vk::ImageView vkImageView_;
  };

  // TextureImageImpl -------------------------------------------------------------------------------------------------

  class BaseTextureImageImpl : public TextureImage
  {
   public:
    explicit BaseTextureImageImpl(Sampler sampler) : sampler_(std::move(sampler))
    {
    }

    void setSampler(Sampler const& sampler) override
    {
      sampler_ = sampler;
    }

    [[nodiscard]] Sampler const& getSampler() const
    {
      return sampler_;
    }

   private:
    Sampler sampler_;
  };

  class TextureImageImpl : public BaseTextureImageImpl, public BaseImageImpl
  {
   public:
    TextureImageImpl(Device const& device, ImageCreateFlags const& createFlags, utils::Extent3D const& extent,
        ImageFormat format, utils::SizeT mipLevelsCount, utils::SizeT arrayLayersCount, SampleCount sampleCount,
        vk::ImageUsageFlags const& usage)
        : BaseTextureImageImpl(Sampler(device)),
          BaseImageImpl(device, createFlags, extent, format, mipLevelsCount, arrayLayersCount, sampleCount, usage)
    {
    }
  };

  class TextureImageViewImpl : public BaseTextureImageImpl, public BaseImageViewImpl
  {
   public:
    TextureImageViewImpl(Device const& device, std::shared_ptr<TextureImage> const& image,
        ImageSubResourceRange const& range, ComponentMapping const& components)
        : BaseTextureImageImpl(Sampler(device)), BaseImageViewImpl(device, image, range, components)
    {
    }
  };

  // ColorAttachmentImageImpl -----------------------------------------------------------------------------------------

  class BaseColorAttachmentImageImpl : public ColorAttachmentImage
  {
   public:
    void setClearColor(std::array<float, 4> const& clearValue) override;

    void setLoadOp(AttachmentLoadOp op) override;

    void setStoreOp(AttachmentStoreOp op) override;

   private:
    VezAttachmentInfo info_ = {VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE, {VkClearColorValue{}}};
  };

  class ColorAttachmentImageImpl : private BaseColorAttachmentImageImpl, public BaseImageImpl
  {
   public:
    using BaseImageImpl::BaseImageImpl;
  };

  class ColorAttachmentImageViewImpl : private BaseColorAttachmentImageImpl, public BaseImageViewImpl
  {
   public:
    using BaseImageViewImpl::BaseImageViewImpl;
  };

  // DepthAttachmentImageImpl -----------------------------------------------------------------------------------------

  class BaseDepthAttachmentImageImpl : public DepthAttachmentImage
  {
   public:
    void setClearColor(float depth, unsigned stencil) override;

    void setLoadOp(AttachmentLoadOp op) override;

    void setStoreOp(AttachmentStoreOp op) override;

   private:
    VezAttachmentInfo info_ = {
        VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE, {VkClearDepthStencilValue{1.0f, 0}}};
  };

  class DepthAttachmentImageImpl : private BaseDepthAttachmentImageImpl, public BaseImageImpl
  {
   public:
    using BaseImageImpl::BaseImageImpl;
  };

  class DepthAttachmentImageViewImpl : private BaseDepthAttachmentImageImpl, public BaseImageViewImpl
  {
   public:
    using BaseImageViewImpl::BaseImageViewImpl;
  };

}  // namespace vulkan