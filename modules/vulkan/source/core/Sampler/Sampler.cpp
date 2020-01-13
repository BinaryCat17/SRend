#include "Sampler.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  vk::BorderColor toVkBorderColor(BorderColor color)
  {
    return static_cast<vk::BorderColor>(color);
  }

  vk::SamplerAddressMode toVkAddressMode(SamplerAddressMode mode)
  {
    return static_cast<vk::SamplerAddressMode>(mode);
  }

  vk::Filter toVkFilter(Filter filter)
  {
    return static_cast<vk::Filter>(filter);
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
    throw std::runtime_error("undefined sampler mip map mode");
  }

  // SamplerImpl ------------------------------------------------------------------------------------------------------

  SamplerImpl::SamplerImpl(std::shared_ptr<DeviceImpl> device, SamplerCreateFlags) : device_(std::move(device))
  {
  }

  SamplerImpl::~SamplerImpl()
  {
    vezDestroySampler(device_->getVkDevice(), vkSampler_);
  }

  void SamplerImpl::update()
  {
    if (needUpdate_)
    {
      VezSamplerCreateInfo createInfo = {};
      createInfo.unnormalizedCoordinates = unnormalizedCoordinates_;
      createInfo.borderColor = static_cast<VkBorderColor>(toVkBorderColor(borderColor_));
      createInfo.compareEnable = compareOp_.has_value();
      if (compareOp_.has_value())
      {
        createInfo.compareOp = static_cast<VkCompareOp>(toVkCompareOp(*compareOp_));
      }
      createInfo.anisotropyEnable = anisotropy_.has_value();
      if (anisotropy_.has_value())
      {
        createInfo.maxAnisotropy = (*anisotropy_);
      }
      createInfo.addressModeU = static_cast<VkSamplerAddressMode>(toVkAddressMode(addressModeU_));
      createInfo.addressModeV = static_cast<VkSamplerAddressMode>(toVkAddressMode(addressModeV_));
      createInfo.addressModeW = static_cast<VkSamplerAddressMode>(toVkAddressMode(addressModeW_));
      createInfo.magFilter = static_cast<VkFilter>(toVkFilter(magFilter_));
      createInfo.minFilter = static_cast<VkFilter>(toVkFilter(minFilter_));
      createInfo.minLod = minLod_;
      createInfo.mipLodBias = mipLodBias_;
      createInfo.maxLod = maxLod_;
      createInfo.mipmapMode = static_cast<VkSamplerMipmapMode>(toVkMipMapMode(mipMapMode_));

      VkSampler result = nullptr;
      checkResult(vezCreateSampler(device_->getVkDevice(), &createInfo, &result));
      vkSampler_ = result;
    }
    needUpdate_ = false;
  }

  // Sampler ----------------------------------------------------------------------------------------------------------

  void Sampler::setMagFilter(Filter const& val)
  {
    pimpl_->setMagFilter(val);
  }

  void Sampler::setMinFilter(Filter const& val)
  {
    pimpl_->setMinFilter(val);
  }

  void Sampler::setMipMapMode(SamplerMipMapMode const& val)
  {
    pimpl_->setMipMapMode(val);
  }

  void Sampler::setAddressModeU(SamplerAddressMode const& val)
  {
    pimpl_->setAddressModeU(val);
  }

  void Sampler::setAddressModeV(SamplerAddressMode const& val)
  {
    pimpl_->setAddressModeV(val);
  }

  void Sampler::setAddressModeW(SamplerAddressMode const& val)
  {
    pimpl_->setAddressModeW(val);
  }

  void Sampler::setMipLodBias(float val)
  {
    pimpl_->setMipLodBias(val);
  }

  void Sampler::enableAnisotropy(float val)
  {
    pimpl_->enableAnisotropy(val);
  }

  void Sampler::disableAnisotropy()
  {
    pimpl_->disableAnisotropy();
  }

  void Sampler::enableCompareOp(CompareOp val)
  {
    pimpl_->enableCompareOp(val);
  }

  void Sampler::disableCompareOp()
  {
    pimpl_->disableCompareOp();
  }

  void Sampler::setMinLod(float val)
  {
    pimpl_->setMinLod(val);
  }

  void Sampler::setMaxLod(float val)
  {
    pimpl_->setMaxLod(val);
  }

  void Sampler::setBorderColor(BorderColor val)
  {
    pimpl_->setBorderColor(val);
  }

  void Sampler::enableUnnormalizedCoordinates()
  {
    pimpl_->enableUnnormalizedCoordinates();
  }

  void Sampler::disableUnnormalizedCoordinates()
  {
    pimpl_->disableUnnormalizedCoordinates();
  }

}  // namespace vulkan