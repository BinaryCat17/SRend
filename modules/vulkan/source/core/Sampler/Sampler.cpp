#include "SamplerImpl.hpp"

namespace vulkan
{
  vulkan::Sampler::Sampler(Device const& device, SamplerFilters const& filters, SamplerMipMapMode mipMapMode,
      SamplerAddressModes const& addressModes, SamplerLODs const& LODs, std::optional<float> maxAnisotropy,
      std::optional<CompareOp> compareOp, BorderColor borderColor, bool unnormalizedCoordinates)
      : pimpl_(std::make_shared<SamplerImpl>(device, filters, mipMapMode, addressModes, LODs, maxAnisotropy, compareOp,
            borderColor, unnormalizedCoordinates))
  {
  }

}  // namespace vulkan