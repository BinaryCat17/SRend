#pragma once
#include "../Device/Device.hpp"
#include "../Sampler/Sampler.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(ImageCreate, {};)

  // clang-format on

  enum class ImageFormat
  {
    Undefined,
    R8Unorm,
    R8Snorm,
    R8Uscaled,
    R8Sscaled,
    R8Uint,
    R8Sint,
    R8Srgb,
    R8G8Unorm,
    R8G8Snorm,
    R8G8Uscaled,
    R8G8Sscaled,
    R8G8Uint,
    R8G8Sint,
    R8G8Srgb,
    R8G8B8Unorm,
    R8G8B8Snorm,
    R8G8B8Uscaled,
    R8G8B8Sscaled,
    R8G8B8Uint,
    R8G8B8Sint,
    R8G8B8Srgb,
    B8G8R8Unorm,
    B8G8R8Snorm,
    B8G8R8Uscaled,
    B8G8R8Sscaled,
    B8G8R8Uint,
    B8G8R8Sint,
    B8G8R8Srgb,
    R8G8B8A8Unorm,
    R8G8B8A8Snorm,
    R8G8B8A8Uscaled,
    R8G8B8A8Sscaled,
    R8G8B8A8Uint,
    R8G8B8A8Sint,
    R8G8B8A8Srgb,
    B8G8R8A8Unorm,
    B8G8R8A8Snorm,
    B8G8R8A8Uscaled,
    B8G8R8A8Sscaled,
    B8G8R8A8Uint,
    B8G8R8A8Sint,
    B8G8R8A8Srgb,
    R16Unorm,
    R16Snorm,
    R16Uscaled,
    R16Sscaled,
    R16Uint,
    R16Sint,
    R16Sfloat,
    R16G16Unorm,
    R16G16Snorm,
    R16G16Uscaled,
    R16G16Sscaled,
    R16G16Uint,
    R16G16Sint,
    R16G16Sfloat,
    R16G16B16Unorm,
    R16G16B16Snorm,
    R16G16B16Uscaled,
    R16G16B16Sscaled,
    R16G16B16Uint,
    R16G16B16Sint,
    R16G16B16Sfloat,
    R16G16B16A16Unorm,
    R16G16B16A16Snorm,
    R16G16B16A16Uscaled,
    R16G16B16A16Sscaled,
    R16G16B16A16Uint,
    R16G16B16A16Sint,
    R16G16B16A16Sfloat,
    R32Uint,
    R32Sint,
    R32Sfloat,
    R32G32Uint,
    R32G32Sint,
    R32G32Sfloat,
    R32G32B32Uint,
    R32G32B32Sint,
    R32G32B32Sfloat,
    R32G32B32A32Uint,
    R32G32B32A32Sint,
    R32G32B32A32Sfloat,
    R64Uint,
    R64Sint,
    R64Sfloat,
    R64G64Uint,
    R64G64Sint,
    R64G64Sfloat,
    R64G64B64Uint,
    R64G64B64Sint,
    R64G64B64Sfloat,
    R64G64B64A64Uint,
    R64G64B64A64Sint,
    R64G64B64A64Sfloat,
    D16Unorm,
    D32Sfloat,
    S8Uint,
    D16UnormS8Uint,
    D24UnormS8Uint,
    D32SfloatS8Uint,
  };

  enum class SampleCount
  {
    e1,
    e2,
    e4,
    e8,
    e16,
    e32,
    e64
  };

  enum class ComponentSwizzle
  {
    Identity,
    Zero,
    One,
    R,
    G,
    B,
    A,
  };

  enum class AttachmentLoadOp
  {
    Load,
    Clear,
    DontCare,
  };

  enum class AttachmentStoreOp
  {
    Store,
    DontCare,
  };

  struct ImageSubResourceRange
  {
    ImageSubResourceRange() = default;

    ImageSubResourceRange(utils::IndexT baseMipLevel, utils::SizeT mipLevelCount, utils::IndexT baseArrayLayer,
        utils::SizeT arrayLayerCount)
        : baseMipLevel(baseMipLevel),
          mipLevelCount(mipLevelCount),
          baseArrayLayer(baseArrayLayer),
          arrayLayerCount(arrayLayerCount)
    {
    }

    ImageSubResourceRange(utils::SizeT mipLevelCount, utils::SizeT arrayLayerCount)
        : mipLevelCount(mipLevelCount), arrayLayerCount(arrayLayerCount)
    {
    }

    utils::IndexT baseMipLevel = 0;
    utils::SizeT mipLevelCount = 1;
    utils::IndexT baseArrayLayer = 0;
    utils::SizeT arrayLayerCount = 1;
  };

  struct ComponentMapping
  {
    ComponentMapping() = default;

    ComponentMapping(ComponentSwizzle r, ComponentSwizzle g, ComponentSwizzle b, ComponentSwizzle a)
        : r(r), g(g), b(b), a(a)
    {
    }

    ComponentSwizzle r = ComponentSwizzle::Identity;
    ComponentSwizzle g = ComponentSwizzle::Identity;
    ComponentSwizzle b = ComponentSwizzle::Identity;
    ComponentSwizzle a = ComponentSwizzle::Identity;
  };

  // Image ------------------------------------------------------------------------------------------------------------

  class Image
  {
   public:
    virtual ~Image() = default;

    [[nodiscard]] virtual ImageFormat getFormat() const = 0;

    [[nodiscard]] virtual utils::Extent3D getExtent() const = 0;

    [[nodiscard]] virtual ImageSubResourceRange getRange() const = 0;

    [[nodiscard]] virtual SampleCount getSampleCount() const = 0;
  };

  // TextureImage -----------------------------------------------------------------------------------------------------

  class TextureImage : public Image
  {
   public:
    virtual void setSampler(Sampler const& sampler) = 0;
  };

  std::shared_ptr<TextureImage> createTextureImage(Device const& device, ImageCreateFlags const& createFlags,
      utils::Extent3D const& extent, ImageFormat format, utils::SizeT mipLevelCount = 1,
      utils::SizeT arrayLayersCount = 1, SampleCount sampleCount = SampleCount::e1);

  std::shared_ptr<TextureImage> createTextureImage(Device const& device, std::shared_ptr<TextureImage> const& image,
      ImageSubResourceRange const& range = {}, ComponentMapping const& components = {});

  // ColorAttachmentImage ---------------------------------------------------------------------------------------------

  class ColorAttachmentImage : public Image
  {
   public:
    virtual void setClearColor(std::array<float, 4> const& clearValue) = 0;

    virtual void setLoadOp(AttachmentLoadOp op) = 0;

    virtual void setStoreOp(AttachmentStoreOp op) = 0;
  };

  std::shared_ptr<ColorAttachmentImage> createColorAttachmentImage(Device const& device,
      ImageCreateFlags const& createFlags, utils::Extent3D const& extent, ImageFormat format,
      utils::SizeT mipLevelCount = 1, utils::SizeT arrayLayersCount = 1, SampleCount sampleCount = SampleCount::e1);

  std::shared_ptr<ColorAttachmentImage> createColorAttachmentImage(Device const& device,
      std::shared_ptr<TextureImage> const& image, ImageSubResourceRange const& range = {},
      ComponentMapping const& components = {});

  // ColorAttachmentImage ---------------------------------------------------------------------------------------------

  class DepthAttachmentImage : public Image
  {
   public:
    virtual void setClearColor(float depth, unsigned stencil) = 0;

    virtual void setLoadOp(AttachmentLoadOp op) = 0;

    virtual void setStoreOp(AttachmentStoreOp op) = 0;
  };

  std::shared_ptr<DepthAttachmentImage> createDepthAttachmentImage(Device const& device,
      ImageCreateFlags const& createFlags, utils::Extent3D const& extent, ImageFormat format,
      utils::SizeT mipLevelCount = 1, utils::SizeT arrayLayersCount = 1, SampleCount sampleCount = SampleCount::e1);

  std::shared_ptr<ColorAttachmentImage> createDepthAttachmentImage(Device const& device,
      std::shared_ptr<TextureImage> const& image, ImageSubResourceRange const& range = {},
      ComponentMapping const& components = {});

}  // namespace vulkan