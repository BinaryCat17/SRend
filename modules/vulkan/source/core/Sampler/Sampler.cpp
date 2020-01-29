#include "Sampler.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

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
      createInfo.borderColor = toVkBorderColor(borderColor_);
      createInfo.compareEnable = compareOp_.has_value();
      if (compareOp_.has_value())
      {
        createInfo.compareOp = toVkCompareOp(*compareOp_);
      }
      createInfo.anisotropyEnable = anisotropy_.has_value();
      if (anisotropy_.has_value())
      {
        createInfo.maxAnisotropy = (*anisotropy_);
      }
      createInfo.addressModeU = toVkAddressMode(addressModeU_);
      createInfo.addressModeV = toVkAddressMode(addressModeV_);
      createInfo.addressModeW = toVkAddressMode(addressModeW_);
      createInfo.magFilter = toVkFilter(magFilter_);
      createInfo.minFilter = toVkFilter(minFilter_);
      createInfo.minLod = minLod_;
      createInfo.mipLodBias = mipLodBias_;
      createInfo.maxLod = maxLod_;
      createInfo.mipmapMode = toVkMipMapMode(mipMapMode_);

      VkSampler result = nullptr;
      checkResult(vezCreateSampler(device_->getVkDevice(), &createInfo, &result));
      vkSampler_ = result;
    }
    needUpdate_ = false;
  }

  // Sampler ----------------------------------------------------------------------------------------------------------

  Sampler::Sampler(Device const& device, SamplerCreateFlags const& createFlags)
      : pimpl_(std::make_shared<SamplerImpl>(device.getImpl(), createFlags))
  {
  }

  void Sampler::setMagFilter(Filter const& val) noexcept
  {
    pimpl_->setMagFilter(val);
  }

  void Sampler::setMinFilter(Filter const& val) noexcept
  {
    pimpl_->setMinFilter(val);
  }

  void Sampler::setMipMapMode(MipMapMode const& val) noexcept
  {
    pimpl_->setMipMapMode(val);
  }

  void Sampler::setAddressModeU(AddressMode const& val) noexcept
  {
    pimpl_->setAddressModeU(val);
  }

  void Sampler::setAddressModeV(AddressMode const& val) noexcept
  {
    pimpl_->setAddressModeV(val);
  }

  void Sampler::setAddressModeW(AddressMode const& val) noexcept
  {
    pimpl_->setAddressModeW(val);
  }

  void Sampler::setMipLodBias(float val) noexcept
  {
    pimpl_->setMipLodBias(val);
  }

  void Sampler::setAnisotropy(std::optional<float> val) noexcept
  {
    pimpl_->setAnisotropy(val);
  }

  void Sampler::setCompareOp(std::optional<CompareOp> val) noexcept
  {
    pimpl_->setCompareOp(val);
  }

  void Sampler::setMinLod(float val) noexcept
  {
    pimpl_->setMinLod(val);
  }

  void Sampler::setMaxLod(float val) noexcept
  {
    pimpl_->setMaxLod(val);
  }

  void Sampler::setBorderColor(BorderColor val) noexcept
  {
    pimpl_->setBorderColor(val);
  }

  void Sampler::setUnnormalizedCoordinates(bool enable) noexcept
  {
    pimpl_->setUnnormalizedCoordinates(enable);
  }

  Filter Sampler::getMagFilter() const noexcept
  {
    return pimpl_->getMagFilter();
  }

  Filter Sampler::getMinFilter() const noexcept
  {
    return pimpl_->getMagFilter();
  }

  MipMapMode Sampler::getMipMapMode() const noexcept
  {
    return pimpl_->getMipMapMode();
  }

  AddressMode Sampler::getAddressModeU() const noexcept
  {
    return pimpl_->getAddressModeU();
  }

  AddressMode Sampler::getAddressModeV() const noexcept
  {
    return pimpl_->getAddressModeV();
  }

  AddressMode Sampler::getAddressModeW() const noexcept
  {
    return pimpl_->getAddressModeW();
  }

  float Sampler::getMipLodBias() const noexcept
  {
    return pimpl_->getMipLodBias();
  }

  std::optional<float> Sampler::getAnisotropy() const noexcept
  {
    return pimpl_->getAnisotropy();
  }

  std::optional<CompareOp> Sampler::getCompareOp() const noexcept
  {
    return pimpl_->getCompareOp();
  }

  float Sampler::getMinLod() const noexcept
  {
    return pimpl_->getMinLod();
  }

  float Sampler::getMaxLod() const noexcept
  {
    return pimpl_->getMaxLod();
  }

  BorderColor Sampler::getBorderColor() const noexcept
  {
    return pimpl_->getBorderColor();
  }

  bool Sampler::getUnnormalizedCoordinates() const noexcept
  {
    return pimpl_->getUnnormalizedCoordinates();
  }

}  // namespace vulkan