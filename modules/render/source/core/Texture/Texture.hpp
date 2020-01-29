#pragma once
#include <assimp/material.h>
#include "../utils.hpp"

namespace render
{
  // TextureImpl -----------------------------------------------------------------------------------------------------

  class TextureImpl
  {
   public:
    explicit TextureImpl(vulkan::Device device, std::filesystem::path const& path);

    void update();

    explicit TextureImpl(vulkan::Device device, aiMaterial const& material, utils::IndexT index);

    explicit TextureImpl(vulkan::Device device, void const* pData, vulkan::Format format,
        utils::Extent2D const& extent, utils::SizeT size);

    void operator()(vulkan::CommandBuffer& commandBuffer, vulkan::BindingInfo const& bindingInfo) const;

   private:
    vulkan::Device device_;
    vulkan::Image image_;
    vulkan::Sampler sampler_;
    std::filesystem::path path_;
    bool updated_ = false;
  };

}  // namespace render