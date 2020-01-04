#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  enum class SamplerAddressMode
  {
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    ClampToBorder,
    MirrorClampToEdge,
  };

  enum class SamplerFilter
  {
    Nearest,
    Linear,
  };

  enum class SamplerMipMapMode
  {
    Nearest,
    Linear,
  };

  enum class CompareOp
  {
    Never,
    Less,
    Equal,
    LessOrEqual,
    Greater,
    NotEqual,
    GreaterOrEqual,
    Always
  };

  enum class BorderColor
  {
    FloatTransparentBlack,
    IntTransparentBlack,
    FloatOpaqueBlack,
    IntOpaqueBlack,
    FloatOpaqueWhite,
    IntOpaqueWhite,
  };

  struct SamplerAddressModes
  {
    SamplerAddressModes() = default;

    SamplerAddressModes(SamplerAddressMode u, SamplerAddressMode v, SamplerAddressMode w) : u(u), v(v), w(w)
    {
    }

    SamplerAddressMode u = SamplerAddressMode::Repeat;
    SamplerAddressMode v = SamplerAddressMode::Repeat;
    SamplerAddressMode w = SamplerAddressMode::Repeat;
  };

  struct SamplerFilters
  {
    SamplerFilters() = default;

    SamplerFilters(SamplerFilter mag, SamplerFilter min) : mag(mag), min(min)
    {
    }

    SamplerFilter mag = SamplerFilter::Nearest;
    SamplerFilter min = SamplerFilter::Nearest;
  };

  struct SamplerLODs
  {
    SamplerLODs() = default;

    SamplerLODs(float mipLodBias, float minLod, float maxLod) : mipLodBias(mipLodBias), minLod(minLod), maxLod(maxLod)
    {
    }

    float mipLodBias = 0.0f;
    float minLod = 0.0f;
    float maxLod = 0.0f;
  };

  // SamplerImpl ------------------------------------------------------------------------------------------------------

  class SamplerImpl;

  class Sampler
  {
   public:
    explicit Sampler(std::shared_ptr<SamplerImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<SamplerImpl> const& getImpl() const
    {
      return pimpl_;
    }

    explicit Sampler(Device const& device, SamplerFilters const& filters = {}, SamplerMipMapMode mipMapMode = {},
        SamplerAddressModes const& addressModes = {}, SamplerLODs const& LODs = {},
        std::optional<float> maxAnisotropy = {}, std::optional<CompareOp> compareOp = {}, BorderColor borderColor = {},
        bool unnormalizedCoordinates = {});

   private:
    std::shared_ptr<SamplerImpl> pimpl_;
  };
}  // namespace vulkan
