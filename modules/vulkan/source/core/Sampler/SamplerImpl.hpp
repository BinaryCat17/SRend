#pragma once
#include "../Device/DeviceImpl.hpp"
#include "Sampler.hpp"

namespace vulkan
{
  // SamplerImpl ------------------------------------------------------------------------------------------------------

  class SamplerImpl
  {
   public:
    explicit SamplerImpl(Device device, SamplerFilters const& filters, SamplerMipMapMode mipMapMode,
        SamplerAddressModes const& addressModes, SamplerLODs const& LODs, std::optional<float> maxAnisotropy,
        std::optional<CompareOp> compareOp, BorderColor borderColor, bool unnormalizedCoordinates);

    ~SamplerImpl();

    [[nodiscard]] vk::Sampler getVkSampler() const
    {
      return vkSampler_;
    }

   private:
    Device device_;
    vk::Sampler vkSampler_;
  };

}  // namespace vulkan
