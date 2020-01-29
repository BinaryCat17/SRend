#pragma once
#include <assimp/material.h>
#include "../utils.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  struct ShaderTextureData
  {
    alignas(4) float blendFactor = {};
    alignas(4) TextureOp textureOp = {};
  };

  struct ShaderTexture
  {
    Texture texture;
    vulkan::Buffer buffer;
    vulkan::BufferMappedData data;
    ShaderTextureData* pData = {};
  };

  // MaterialImpl -----------------------------------------------------------------------------------------------------

  class MaterialImpl
  {
   public:
    explicit MaterialImpl(vulkan::Device device, MaterialData materialData)
        : device_(std::move(device)), materialData_(std::move(materialData))
    {
    }

    explicit MaterialImpl(vulkan::Device device, aiMaterial const& aiMaterial);

    void operator()(vulkan::CommandBuffer& commandBuffer) const;

    void setMaterialData(MaterialData const& material)
    {
      materialData_ = material;
    }

    [[nodiscard]] MaterialData getMaterialData() const
    {
      return materialData_;
    }

    [[nodiscard]] utils::SizeT getDiffuseTextureCount() const
    {
      return diffuseTextures_.size();
    }

    void addDiffuseTexture(Texture const& texture, float blendFactor = 1.0f, TextureOp op = TextureOp::Add);

    void removeDiffuseTexture(utils::IndexT index)
    {
      diffuseTextures_.erase(diffuseTextures_.begin() + index);
    }

    [[nodiscard]] Texture getDiffuseTexture(utils::IndexT index) const
    {
      return diffuseTextures_[index].texture;
    }

    [[nodiscard]] float getDiffuseTextureBlendFactor(utils::IndexT index) const
    {
      return diffuseTextures_[index].pData->blendFactor;
    }

    [[nodiscard]] TextureOp getDiffuseTextureOp(utils::IndexT index) const
    {
      return diffuseTextures_[index].pData->textureOp;
    }

    [[nodiscard]] utils::SizeT getAmbientTextureCount() const
    {
      return ambientTextures_.size();
    }

    void addAmbientTexture(Texture const& texture, float blendFactor = 1.0f, TextureOp op = TextureOp::Add);

    void removeAmbientTexture(utils::IndexT index)
    {
      ambientTextures_.erase(diffuseTextures_.begin() + index);
    }

    [[nodiscard]] Texture getAmbientTexture(utils::IndexT index) const
    {
      return ambientTextures_[index].texture;
    }

    [[nodiscard]] float getAmbientTextureBlendFactor(utils::IndexT index) const
    {
      return ambientTextures_[index].pData->blendFactor;
    }

    [[nodiscard]] TextureOp getAmbientTextureOp(utils::IndexT index) const
    {
      return ambientTextures_[index].pData->textureOp;
    }

    [[nodiscard]] utils::SizeT getSpecularTextureCount() const
    {
      return specularTextures_.size();
    }

    void addSpecularTexture(Texture const& texture, float blendFactor = 1.0f, TextureOp op = TextureOp::Add);

    void removeSpecularTexture(utils::IndexT index)
    {
      specularTextures_.erase(diffuseTextures_.begin() + index);
    }

    [[nodiscard]] Texture getSpecularTexture(utils::IndexT index) const
    {
      return specularTextures_[index].texture;
    }

    [[nodiscard]] float getSpecularTextureBlendFactor(utils::IndexT index) const
    {
      return specularTextures_[index].pData->blendFactor;
    }

    [[nodiscard]] TextureOp getSpecularTextureOp(utils::IndexT index) const
    {
      return specularTextures_[index].pData->textureOp;
    }

   private:
    vulkan::Device device_;
    MaterialData materialData_;
    std::vector<ShaderTexture> diffuseTextures_;
    std::vector<ShaderTexture> specularTextures_;
    std::vector<ShaderTexture> ambientTextures_;
  };

}  // namespace render