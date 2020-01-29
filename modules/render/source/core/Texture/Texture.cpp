#include "Texture.hpp"
#include "../../../include/render/core.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  vulkan::Image createTextureImage(vulkan::Device& device, std::string const& path)
  {
    int texWidth = 0, texHeight = 0, texChannels = 0;
    stbi_uc* pixels = stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    utils::SizeT imageSize = texWidth * texHeight * 4;

    if (!pixels)
    {
      throw std::runtime_error("failed to load texture image!");
    }

    return createSampledImage(device,
        utils::Extent3D{static_cast<unsigned>(texWidth), static_cast<unsigned>(texHeight), 1},
        vulkan::Format::R8G8B8A8Unorm, pixels, imageSize);
  }

  vulkan::Image getAiDiffuseTexture(vulkan::Device& device, aiMaterial const& material, utils::IndexT index)
  {
    aiString texturePath;
    material.GetTexture(aiTextureType_DIFFUSE, index, &texturePath);
    return createTextureImage(device, texturePath.data);
  }

  // TextureImpl -----------------------------------------------------------------------------------------------------

  TextureImpl::TextureImpl(vulkan::Device device, std::filesystem::path const& path)
      : device_(device), image_(nullptr), sampler_(device_), path_(path)
  {
  }

  TextureImpl::TextureImpl(vulkan::Device device, aiMaterial const& material, utils::IndexT index)
      : device_(device), image_(getAiDiffuseTexture(device, material, index)), sampler_(device)
  {
    updated_ = true;
  }

  TextureImpl::TextureImpl(
      vulkan::Device device, void const* pData, vulkan::Format format, utils::Extent2D const& extent, utils::SizeT size)
      : device_(device),
        image_(createSampledImage(device, utils::Extent3D(extent), format, pData, size)),
        sampler_(device)
  {
    updated_ = true;
  }

  void TextureImpl::operator()(vulkan::CommandBuffer& commandBuffer, vulkan::BindingInfo const& bindingInfo) const
  {
    if (updated_)
    {
      commandBuffer.bindImage(image_, sampler_, bindingInfo);
    }
  }

  void TextureImpl::update()
  {
    if (!updated_)
    {
      updated_ = true;
      image_ = createTextureImage(device_, path_.string());
    }
  }

  // Texture ----------------------------------------------------------------------------------------------------------

  Texture::Texture(vulkan::Device const& device, std::filesystem::path const& path)
      : pimpl_(std::make_shared<TextureImpl>(device, path))
  {
  }

  Texture::Texture(vulkan::Device& device, void const* pData, vulkan::Format format, utils::Extent2D const& extent,
      utils::SizeT size)
      : pimpl_(std::make_shared<TextureImpl>(device, pData, format, extent, size))
  {
  }
  void Texture::update()
  {
    pimpl_->update();
  }

}  // namespace render