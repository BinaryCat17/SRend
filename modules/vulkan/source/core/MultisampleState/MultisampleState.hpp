#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // MultisampleStateImpl ---------------------------------------------------------------------------------------------

  class MultisampleStateImpl
  {
   public:
    explicit MultisampleStateImpl(std::shared_ptr<DeviceImpl> const&, MultisampleStateCreateFlags const&)
    {
    }

    MultisampleStateImpl(MultisampleStateImpl const&) = delete;

    MultisampleStateImpl(MultisampleStateImpl&&) = delete;

    MultisampleStateImpl& operator=(MultisampleStateImpl const&) = delete;

    MultisampleStateImpl& operator=(MultisampleStateImpl&&) = delete;

    [[nodiscard]] VezMultisampleState const& getVkMultisampleState() const
    {
      return multisampleState_;
    }

    void setRasterizationSamples(SampleCountFlagBits val) noexcept
    {
      multisampleState_.rasterizationSamples = toVkSampleCount(val);
    }

    void setSampleShading(std::optional<float> val) noexcept
    {
      multisampleState_.sampleShadingEnable = val.has_value();
      multisampleState_.minSampleShading = val.has_value() ? *val : 0;
    }

    void setSampleMask(uint32_t val) noexcept
    {
      sampleMask_ = val;
      multisampleState_.pSampleMask = &sampleMask_;
    }

    void setAlphaToCoverage(bool val) noexcept
    {
      multisampleState_.alphaToCoverageEnable = val;
    }

    void setAlphaToOne(bool val) noexcept
    {
      multisampleState_.alphaToOneEnable = val;
    }

    [[nodiscard]] SampleCountFlagBits getRasterizationSamples() const noexcept
    {
      return static_cast<SampleCountFlagBits>(multisampleState_.rasterizationSamples);
    }

    [[nodiscard]] std::optional<float> getSampleShading() const noexcept
    {
      return multisampleState_.sampleShadingEnable ? multisampleState_.minSampleShading : std::optional<float>();
    }

    [[nodiscard]] uint32_t getSampleMask() const noexcept
    {
      return sampleMask_;
    }

    [[nodiscard]] bool getAlphaToCoverage() const noexcept
    {
      return multisampleState_.alphaToCoverageEnable;
    }

    [[nodiscard]] bool getAlphaToOne() const noexcept
    {
      return multisampleState_.alphaToOneEnable;
    }

   private:
    uint32_t sampleMask_ = 0;
    VezMultisampleState multisampleState_ = {};
  };

}  // namespace vulkan