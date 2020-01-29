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

    void update();

    void setMagFilter(Filter const& val) noexcept
    {
      magFilter_ = val;
    }

    void setMinFilter(Filter const& val) noexcept
    {
      minFilter_ = val;
    }

    void setMipMapMode(MipMapMode const& val) noexcept
    {
      mipMapMode_ = val;
    }

    void setAddressModeU(AddressMode const& val) noexcept
    {
      addressModeU_ = val;
    }

    void setAddressModeV(AddressMode const& val) noexcept
    {
      addressModeV_ = val;
    }

    void setAddressModeW(AddressMode const& val) noexcept
    {
      addressModeW_ = val;
    }

    void setMipLodBias(float val) noexcept
    {
      mipLodBias_ = val;
    }

    void setAnisotropy(std::optional<float> val) noexcept
    {
      anisotropy_ = val;
    }

    void setCompareOp(std::optional<CompareOp> val) noexcept
    {
      compareOp_ = val;
    }

    void setMinLod(float val) noexcept
    {
      minLod_ = val;
    }

    void setMaxLod(float val) noexcept
    {
      maxLod_ = val;
    }

    void setBorderColor(BorderColor val) noexcept
    {
      borderColor_ = val;
    }

    void setUnnormalizedCoordinates(bool val) noexcept
    {
      unnormalizedCoordinates_ = val;
    }

    [[nodiscard]] Filter getMagFilter() const noexcept
    {
      return magFilter_;
    }

    [[nodiscard]] Filter getMinFilter() const noexcept
    {
      return  minFilter_;
    }

    [[nodiscard]] MipMapMode getMipMapMode() const noexcept
    {
      return mipMapMode_;
    }

    [[nodiscard]] AddressMode getAddressModeU() const noexcept
    {
      return addressModeU_;
    }

    [[nodiscard]] AddressMode getAddressModeV() const noexcept
    {
      return addressModeV_;
    }

    [[nodiscard]] AddressMode getAddressModeW() const noexcept
    {
      return addressModeW_;
    }

    [[nodiscard]] float getMipLodBias() const noexcept
    {
      return mipLodBias_;
    }

    [[nodiscard]] std::optional<float> getAnisotropy() const noexcept
    {
      return anisotropy_;
    }

    [[nodiscard]] std::optional<CompareOp> getCompareOp() const noexcept
    {
      return compareOp_;
    }

    [[nodiscard]] float getMinLod() const noexcept
    {
      return minLod_;
    }

    [[nodiscard]] float getMaxLod() const noexcept
    {
      return maxLod_;
    }

    [[nodiscard]] BorderColor getBorderColor() const noexcept
    {
      return borderColor_;
    }

    [[nodiscard]] bool getUnnormalizedCoordinates() const noexcept
    {
      return unnormalizedCoordinates_;
    }

   private:
    std::shared_ptr<DeviceImpl> device_;
    Filter magFilter_ = vulkan::Filter::Linear;
    Filter minFilter_ = vulkan::Filter::Linear;
    MipMapMode mipMapMode_ =  vulkan::MipMapMode::Linear;
    AddressMode addressModeU_ = vulkan::AddressMode::ClampToEdge;
    AddressMode addressModeV_ = vulkan::AddressMode::ClampToEdge;
    AddressMode addressModeW_ = vulkan::AddressMode::ClampToEdge;
    float mipLodBias_ = {};
    std::optional<float> anisotropy_ = {};
    std::optional<CompareOp> compareOp_ = {};
    float minLod_ = {};
    float maxLod_ = {};
    BorderColor borderColor_ = vulkan::BorderColor::FloatOpaqueWhite;
    bool unnormalizedCoordinates_ = {};
    vk::Sampler vkSampler_ = {};
    bool needUpdate_ = true;
  };

}  // namespace vulkan
