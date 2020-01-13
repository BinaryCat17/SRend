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

    void setRasterizationSamples(SampleCountFlagBits sampleCount)
    {
      multisampleState_.rasterizationSamples = static_cast<VkSampleCountFlagBits>(toVkSampleCount(sampleCount));
    }

    void enableSampleShading(float minSampleShading)
    {
      multisampleState_.sampleShadingEnable = true;
      multisampleState_.minSampleShading = minSampleShading;
    }

    void disableSampleShading()
    {
      multisampleState_.sampleShadingEnable = false;
    }

    void setSampleMask(uint32_t mask)
    {
      sampleMask_ = mask;
      multisampleState_.pSampleMask = &sampleMask_;
    }

    void enableAlphaToCoverage()
    {
      multisampleState_.alphaToCoverageEnable = true;
    }

    void disableAlphaToCoverage()
    {
      multisampleState_.alphaToCoverageEnable = false;
    }

    void enableAlphaToOne()
    {
      multisampleState_.alphaToOneEnable = true;
    }

    void disableAlphaToOne()
    {
      multisampleState_.alphaToOneEnable = false;
    }

   private:
    uint32_t sampleMask_ = 0;
    VezMultisampleState multisampleState_ = {};
  };

}  // namespace vulkan