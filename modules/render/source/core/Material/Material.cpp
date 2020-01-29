#include "Material.hpp"
#include "../MaterialData/MaterialData.hpp"
#include "../Texture/Texture.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  void addTexture(vulkan::Device& device, std::vector<ShaderTexture>& textures, Texture const& texture,
      ShaderTextureData const& data)
  {
    vulkan::Buffer buffer = createUniformBuffer(device, &data, sizeof(ShaderTextureData));
    auto mappedData = buffer.mapMemory(sizeof(ShaderTextureData));
    textures.push_back({texture, buffer, mappedData, mappedData.pT<ShaderTextureData>()});
  }

  void getAiTextures(
      vulkan::Device& device, std::vector<ShaderTexture>& textures, aiMaterial const& material, aiTextureType type)
  {
    for (utils::IndexT i = 0; i != material.GetTextureCount(type); ++i)
    {
      ShaderTextureData shaderData_ = {};
      aiString path;
      material.GetTexture(type, i, &path, nullptr, nullptr, &shaderData_.blendFactor,
          reinterpret_cast<aiTextureOp*>(shaderData_.textureOp));

      addTexture(device, textures, Texture(device, std::filesystem::path(path.data)), shaderData_);
    }
  }

  // MaterialImpl -----------------------------------------------------------------------------------------------------

  MaterialImpl::MaterialImpl(vulkan::Device device, aiMaterial const& aiMaterial)
      : device_(std::move(device)), materialData_(std::make_shared<MaterialDataImpl>(device_, aiMaterial))
  {
    getAiTextures(device_, diffuseTextures_, aiMaterial, aiTextureType_DIFFUSE);
    getAiTextures(device_, specularTextures_, aiMaterial, aiTextureType_SPECULAR);
    getAiTextures(device_, ambientTextures_, aiMaterial, aiTextureType_AMBIENT);
  }

  void MaterialImpl::operator()(vulkan::CommandBuffer& commandBuffer) const
  {
    (*materialData_.getImpl())(commandBuffer);

    for (utils::IndexT i = 0; i != diffuseTextures_.size(); ++i)
    {
      (*diffuseTextures_[i].texture.getImpl())(commandBuffer, vulkan::BindingInfo(1, i));
      commandBuffer.bindBuffer(diffuseTextures_[i].buffer, vulkan::BindingInfo(2, i));
    }
    for (utils::IndexT i = 0; i != specularTextures_.size(); ++i)
    {
      (*specularTextures_[i].texture.getImpl())(commandBuffer, vulkan::BindingInfo(1, i));
      commandBuffer.bindBuffer(specularTextures_[i].buffer, vulkan::BindingInfo(2, i));
    }
    for (utils::IndexT i = 0; i != ambientTextures_.size(); ++i)
    {
      (*ambientTextures_[i].texture.getImpl())(commandBuffer, vulkan::BindingInfo(1, i));
      commandBuffer.bindBuffer(ambientTextures_[i].buffer, vulkan::BindingInfo(2, i));
    }
  }

  void MaterialImpl::addDiffuseTexture(Texture const& texture, float blendFactor, TextureOp op)
  {
    addTexture(device_, diffuseTextures_, texture, ShaderTextureData{blendFactor, op});
  }

  void MaterialImpl::addAmbientTexture(Texture const& texture, float blendFactor, TextureOp op)
  {
    addTexture(device_, ambientTextures_, texture, ShaderTextureData{blendFactor, op});
  }

  void MaterialImpl::addSpecularTexture(Texture const& texture, float blendFactor, TextureOp op)
  {
    addTexture(device_, specularTextures_, texture, ShaderTextureData{blendFactor, op});
  }

  // Material ---------------------------------------------------------------------------------------------------------

  Material::Material(vulkan::Device const& device, MaterialData const& materialData)
      : pimpl_(std::make_shared<MaterialImpl>(device, materialData))
  {
  }

  void Material::setMaterialData(MaterialData const& material)
  {
    pimpl_->setMaterialData(material);
  }

  [[nodiscard]] MaterialData Material::getMaterialData() const
  {
    return pimpl_->getMaterialData();
  }

  [[nodiscard]] utils::SizeT Material::getDiffuseTextureCount() const
  {
    return pimpl_->getDiffuseTextureCount();
  }

  void Material::addDiffuseTexture(Texture const& texture, float blendFactor, TextureOp op)
  {
    pimpl_->addDiffuseTexture(texture, blendFactor, op);
  }

  void Material::removeDiffuseTexture(utils::IndexT index)
  {
    pimpl_->removeDiffuseTexture(index);
  }

  [[nodiscard]] Texture Material::getDiffuseTexture(utils::IndexT index) const
  {
    return pimpl_->getDiffuseTexture(index);
  }

  [[nodiscard]] float Material::getDiffuseTextureBlendFactor(utils::IndexT index) const
  {
    return pimpl_->getDiffuseTextureBlendFactor(index);
  }

  [[nodiscard]] TextureOp Material::getDiffuseTextureOp(utils::IndexT index) const
  {
    return pimpl_->getDiffuseTextureOp(index);
  }

  [[nodiscard]] utils::SizeT Material::getSpecularTextureCount() const
  {
    return pimpl_->getSpecularTextureCount();
  }

  void Material::addSpecularTexture(Texture const& texture, float blendFactor, TextureOp op)
  {
    pimpl_->addSpecularTexture(texture, blendFactor, op);
  }

  void Material::removeSpecularTexture(utils::IndexT index)
  {
    pimpl_->removeSpecularTexture(index);
  }

  [[nodiscard]] Texture Material::getSpecularTexture(utils::IndexT index) const
  {
    return pimpl_->getSpecularTexture(index);
  }

  [[nodiscard]] float Material::getSpecularTextureBlendFactor(utils::IndexT index) const
  {
    return pimpl_->getSpecularTextureBlendFactor(index);
  }

  [[nodiscard]] TextureOp Material::getSpecularTextureOp(utils::IndexT index) const
  {
    return pimpl_->getSpecularTextureOp(index);
  }

  [[nodiscard]] utils::SizeT Material::getAmbientTextureCount() const
  {
    return pimpl_->getAmbientTextureCount();
  }

  void Material::addAmbientTexture(Texture const& texture, float blendFactor, TextureOp op)
  {
    return pimpl_->addAmbientTexture(texture, blendFactor, op);
  }

  void Material::removeAmbientTexture(utils::IndexT index)
  {
    pimpl_->removeAmbientTexture(index);
  }

  [[nodiscard]] Texture Material::getAmbientTexture(utils::IndexT index) const
  {
    return pimpl_->getAmbientTexture(index);
  }

  [[nodiscard]] float Material::getAmbientTextureBlendFactor(utils::IndexT index) const
  {
    return pimpl_->getAmbientTextureBlendFactor(index);
  }

  [[nodiscard]] TextureOp Material::getAmbientTextureOp(utils::IndexT index) const
  {
    return pimpl_->getAmbientTextureOp(index);
  }

}  // namespace render