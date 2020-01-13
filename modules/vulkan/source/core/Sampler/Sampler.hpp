#pragma once
#include "../Device/Device.hpp"
#include "Sampler.hpp"

namespace vulkan
{
  // SamplerImpl ------------------------------------------------------------------------------------------------------

  class SamplerImpl
  {
   public:
    explicit SamplerImpl(std::shared_ptr<DeviceImpl> device, SamplerCreateFlags createFlags);

    SamplerImpl(SamplerImpl const&) = delete;

    SamplerImpl(SamplerImpl&&) = delete;

    SamplerImpl& operator=(SamplerImpl const&) = delete;

    SamplerImpl& operator=(SamplerImpl&&) = delete;

    ~SamplerImpl();

    [[nodiscard]] std::shared_ptr<DeviceImpl> getDevice() const
    {
      return device_;
    }

    [[nodiscard]] vk::Sampler getVkSampler() const
    {
      return vkSampler_;
    }

    void setMagFilter(Filter const& val)
    {
      magFilter_ = val;
      needUpdate_ = true;
    }

    void setMinFilter(Filter const& val)
    {
      magFilter_ = val;
      needUpdate_ = true;
    }

    void setMipMapMode(SamplerMipMapMode const& val)
    {
      mipMapMode_ = val;
      needUpdate_ = true;
    }

    void setAddressModeU(SamplerAddressMode const& val)
    {
      addressModeU_ = val;
      needUpdate_ = true;
    }

    void setAddressModeV(SamplerAddressMode const& val)
    {
      addressModeV_ = val;
      needUpdate_ = true;
    }

    void setAddressModeW(SamplerAddressMode const& val)
    {
      addressModeW_ = val;
      needUpdate_ = true;
    }

    void setMipLodBias(float val)
    {
      mipLodBias_ = val;
      needUpdate_ = true;
    }

    void enableAnisotropy(float val)
    {
      anisotropy_ = val;
      needUpdate_ = true;
    }

    void disableAnisotropy()
    {
      anisotropy_.reset();
      needUpdate_ = true;
    }

    void enableCompareOp(CompareOp val)
    {
      compareOp_ = val;
      needUpdate_ = true;
    }

    void disableCompareOp()
    {
      compareOp_.reset();
      needUpdate_ = true;
    }

    void setMinLod(float val)
    {
      minLod_ = val;
      needUpdate_ = true;
    }

    void setMaxLod(float val)
    {
      maxLod_ = val;
      needUpdate_ = true;
    }

    void setBorderColor(BorderColor val)
    {
      borderColor_ = val;
      needUpdate_ = true;
    }

    void enableUnnormalizedCoordinates()
    {
      unnormalizedCoordinates_ = true;
      needUpdate_ = true;
    }

    void disableUnnormalizedCoordinates()
    {
      unnormalizedCoordinates_ = false;
      needUpdate_ = true;
    }

    void update();

   private:
    std::shared_ptr<DeviceImpl> device_;
    Filter magFilter_ = {};
    Filter minFilter_ = {};
    SamplerMipMapMode mipMapMode_ = {};
    SamplerAddressMode addressModeU_ = {};
    SamplerAddressMode addressModeV_ = {};
    SamplerAddressMode addressModeW_ = {};
    float mipLodBias_ = {};
    std::optional<float> anisotropy_ = {};
    std::optional<CompareOp> compareOp_ = {};
    float minLod_ = {};
    float maxLod_ = {};
    BorderColor borderColor_ = {};
    bool unnormalizedCoordinates_ = {};
    vk::Sampler vkSampler_ = {};
    bool needUpdate_ = true;
  };

}  // namespace vulkan
