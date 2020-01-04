#include "SamplerImpl.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  vk::BorderColor toVkBorderColor(BorderColor color)
  {
    switch (color)
    {
      case BorderColor::FloatTransparentBlack:
        return vk::BorderColor::eFloatTransparentBlack;
      case BorderColor::IntTransparentBlack:
        return vk::BorderColor::eIntTransparentBlack;
      case BorderColor::FloatOpaqueBlack:
        return vk::BorderColor::eFloatOpaqueBlack;
      case BorderColor::IntOpaqueBlack:
        return vk::BorderColor::eIntOpaqueBlack;
      case BorderColor::FloatOpaqueWhite:
        return vk::BorderColor::eFloatOpaqueWhite;
      case BorderColor::IntOpaqueWhite:
        return vk::BorderColor::eIntOpaqueWhite;
    }
  }

  vk::CompareOp toVkCompareOp(CompareOp op)
  {
    switch (op)
    {
      case CompareOp::Never:
        return vk::CompareOp::eNever;
      case CompareOp::Less:
        return vk::CompareOp::eLess;
      case CompareOp::Equal:
        return vk::CompareOp::eEqual;
      case CompareOp::LessOrEqual:
        return vk::CompareOp::eLessOrEqual;
      case CompareOp::Greater:
        return vk::CompareOp::eGreater;
      case CompareOp::NotEqual:
        return vk::CompareOp::eNotEqual;
      case CompareOp::GreaterOrEqual:
        return vk::CompareOp::eGreaterOrEqual;
      case CompareOp::Always:
        return vk::CompareOp::eAlways;
    }
  }

  vk::SamplerAddressMode toVkAddressMode(SamplerAddressMode mode)
  {
    switch (mode)
    {
      case SamplerAddressMode::Repeat:
        return vk::SamplerAddressMode::eRepeat;
      case SamplerAddressMode::MirroredRepeat:
        return vk::SamplerAddressMode::eMirroredRepeat;
      case SamplerAddressMode::ClampToEdge:
        return vk::SamplerAddressMode::eClampToEdge;
      case SamplerAddressMode::ClampToBorder:
        return vk::SamplerAddressMode::eClampToEdge;
      case SamplerAddressMode::MirrorClampToEdge:
        return vk::SamplerAddressMode::eMirrorClampToEdge;
    }
  }

  vk::Filter toVkFilter(SamplerFilter filter)
  {
    switch (filter)
    {
      case SamplerFilter::Nearest:
        return vk::Filter::eNearest;
      case SamplerFilter::Linear:
        return vk::Filter::eLinear;
    }
  }

  vk::SamplerMipmapMode toVkMipMapMode(SamplerMipMapMode mode)
  {
    switch (mode)
    {
      case SamplerMipMapMode::Nearest:
        return vk::SamplerMipmapMode::eNearest;
      case SamplerMipMapMode::Linear:
        return vk::SamplerMipmapMode::eLinear;
    }
  }

  vk::Sampler createVkSampler(Device const& device, SamplerFilters const& filters, SamplerMipMapMode mipMapMode,
      SamplerAddressModes const& addressModes, SamplerLODs const& LODs, std::optional<float> maxAnisotropy,
      std::optional<CompareOp> compareOp, BorderColor borderColor, bool unnormalizedCoordinates)
  {
    VezSamplerCreateInfo createInfo = {};
    createInfo.unnormalizedCoordinates = unnormalizedCoordinates;
    createInfo.borderColor = static_cast<VkBorderColor>(toVkBorderColor(borderColor));
    createInfo.compareEnable = compareOp.has_value();
    if (compareOp.has_value())
    {
      createInfo.compareOp = static_cast<VkCompareOp>(toVkCompareOp(*compareOp));
    }
    createInfo.anisotropyEnable = maxAnisotropy.has_value();
    if (maxAnisotropy.has_value())
    {
      createInfo.maxAnisotropy = (*maxAnisotropy);
    }
    createInfo.addressModeU = static_cast<VkSamplerAddressMode>(toVkAddressMode(addressModes.u));
    createInfo.addressModeV = static_cast<VkSamplerAddressMode>(toVkAddressMode(addressModes.v));
    createInfo.addressModeW = static_cast<VkSamplerAddressMode>(toVkAddressMode(addressModes.w));
    createInfo.magFilter = static_cast<VkFilter>(toVkFilter(filters.mag));
    createInfo.minFilter = static_cast<VkFilter>(toVkFilter(filters.min));
    createInfo.minLod = LODs.minLod;
    createInfo.mipLodBias = LODs.mipLodBias;
    createInfo.maxLod = LODs.maxLod;
    createInfo.mipmapMode = static_cast<VkSamplerMipmapMode>(toVkMipMapMode(mipMapMode));

    VkSampler result = nullptr;
    checkResult(vezCreateSampler(device.getImpl()->getVkDevice(), &createInfo, &result));
    return result;
  }

  // SamplerImpl ------------------------------------------------------------------------------------------------------

  SamplerImpl::SamplerImpl(Device device, SamplerFilters const& filters, SamplerMipMapMode mipMapMode,
      SamplerAddressModes const& addressModes, SamplerLODs const& LODs, std::optional<float> maxAnisotropy,
      std::optional<CompareOp> compareOp, BorderColor borderColor, bool unnormalizedCoordinates)
      : device_(std::move(device)),
        vkSampler_(createVkSampler(device_, filters, mipMapMode, addressModes, LODs, maxAnisotropy, compareOp,
            borderColor, unnormalizedCoordinates))
  {
  }

  SamplerImpl::~SamplerImpl()
  {
    vezDestroySampler(device_.getImpl()->getVkDevice(), vkSampler_);
  }

}  // namespace vulkan