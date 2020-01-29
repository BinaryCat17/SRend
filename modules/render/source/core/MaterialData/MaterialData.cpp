#include "MaterialData.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  glm::vec3 getAiDiffuseColor(aiMaterial const& material)
  {
    aiColor3D color;
    material.Get(AI_MATKEY_COLOR_DIFFUSE, color);

    return glm::vec3(color.r, color.g, color.b);
  }

  glm::vec3 getAiSpecularColor(aiMaterial const& material)
  {
    aiColor3D color;
    material.Get(AI_MATKEY_COLOR_SPECULAR, color);

    return glm::vec3(color.r, color.g, color.b);
  }

  glm::vec3 getAiAmbientColor(aiMaterial const& material)
  {
    aiColor3D color;
    material.Get(AI_MATKEY_COLOR_AMBIENT, color);

    return glm::vec3(color.r, color.g, color.b);
  }

  glm::vec3 getAiTransparentColor(aiMaterial const& material)
  {
    aiColor3D color;
    material.Get(AI_MATKEY_COLOR_TRANSPARENT, color);

    return glm::vec3(color.r, color.g, color.b);
  }

  bool getAiWireframe(aiMaterial const& material)
  {
    bool val = false;
    material.Get(AI_MATKEY_ENABLE_WIREFRAME, val);
    return val;
  }

  bool getAiTwoSided(aiMaterial const& material)
  {
    bool val = false;
    material.Get(AI_MATKEY_TWOSIDED, val);
    return val;
  }

  ShadingModel getAiShadingModel(aiMaterial const& material)
  {
    int val = false;
    material.Get(AI_MATKEY_SHADING_MODEL, val);
    return static_cast<ShadingModel>(aiShadingMode_Phong);
  }

  BlendMode getAiBlendMode(aiMaterial const& material)
  {
    int val = false;
    material.Get(AI_MATKEY_BLEND_FUNC, val);
    return static_cast<BlendMode>(val);
  }

  float getAiOpacity(aiMaterial const& material)
  {
    float val = false;
    material.Get(AI_MATKEY_OPACITY, val);
    return val;
  }

  float getAiShininess(aiMaterial const& material)
  {
    float val = false;
    material.Get(AI_MATKEY_SHININESS, val);
    return val;
  }

  float getAiShininessStrength(aiMaterial const& material)
  {
    float val = false;
    material.Get(AI_MATKEY_SHININESS_STRENGTH, val);
    return val;
  }

  vulkan::Buffer createMaterialDataBuffer(vulkan::Device& device, aiMaterial const& aiMaterial)
  {
    ShaderMaterialData data;
    data.diffuseColor = getAiDiffuseColor(aiMaterial);
    data.specularColor = getAiSpecularColor(aiMaterial);
    data.ambientColor = getAiAmbientColor(aiMaterial);
    data.transparentColor = getAiTransparentColor(aiMaterial);
    data.wireframe = getAiWireframe(aiMaterial);
    data.twoSided = getAiTwoSided(aiMaterial);
    data.shadingModel = getAiShadingModel(aiMaterial);
    data.blendMode = getAiBlendMode(aiMaterial);
    data.opacity = getAiOpacity(aiMaterial);
    data.shininess = getAiShininess(aiMaterial);
    data.shininessStrength = getAiShininessStrength(aiMaterial);

    return createUniformBuffer(device, &data, sizeof(ShaderMaterialData));
  }

  // MaterialDataImpl -------------------------------------------------------------------------------------------------

  MaterialDataImpl::MaterialDataImpl(vulkan::Device device)
      : buffer_(createUniformBuffer(device, nullptr, sizeof(ShaderMaterialData))),
        data_(buffer_.mapMemory(buffer_.getSize())),
        pData_(data_.pT<ShaderMaterialData>())
  {
  }

  MaterialDataImpl::MaterialDataImpl(vulkan::Device device, aiMaterial const& aiMaterial)
      : buffer_(createMaterialDataBuffer(device, aiMaterial)),
        data_(buffer_.mapMemory(buffer_.getSize())),
        pData_(data_.pT<ShaderMaterialData>()),
        name_(const_cast<struct aiMaterial&>(aiMaterial).GetName().data)
  {
  }

  void MaterialDataImpl::operator()(vulkan::CommandBuffer& commandBuffer) const
  {
    commandBuffer.bindBuffer(buffer_, vulkan::BindingInfo(0, 0, 0));
  }

  // MaterialData -----------------------------------------------------------------------------------------------------

  MaterialData::MaterialData(vulkan::Device const& device) : pimpl_(std::make_shared<MaterialDataImpl>(device))
  {
  }

  [[nodiscard]] std::string MaterialData::getName() const
  {
    return pimpl_->getName();
  }

  void MaterialData::setName(std::string const& name)
  {
    pimpl_->setName(name);
  }

  [[nodiscard]] glm::vec3 MaterialData::getDiffuseColor() const
  {
    return pimpl_->getDiffuseColor();
  }

  void MaterialData::setDiffuseColor(glm::vec3 const& diffuseColor)
  {
    pimpl_->setDiffuseColor(diffuseColor);
  }

  [[nodiscard]] glm::vec3 MaterialData::getSpecularColor() const
  {
    return pimpl_->getSpecularColor();
  }

  void MaterialData::setSpecularColor(glm::vec3 const& specularColor)
  {
    pimpl_->setSpecularColor(specularColor);
  }

  [[nodiscard]] glm::vec3 MaterialData::getAmbientColor() const
  {
    return pimpl_->getAmbientColor();
  }

  void MaterialData::setAmbientColor(glm::vec3 const& ambientColor)
  {
    pimpl_->setAmbientColor(ambientColor);
  }

  [[nodiscard]] glm::vec3 MaterialData::getTransparentColor() const
  {
    return pimpl_->getTransparentColor();
  }

  void MaterialData::setTransparentColor(glm::vec3 const& transparentColor)
  {
    pimpl_->setTransparentColor(transparentColor);
  }

  bool MaterialData::isWireframe() const
  {
    return pimpl_->isWireframe();
  }

  void MaterialData::setWireframe(bool wireframe)
  {
    pimpl_->setWireframe(wireframe);
  }

  [[nodiscard]] bool MaterialData::isTwoSided() const
  {
    return pimpl_->isTwoSided();
  }

  void MaterialData::setTwoSided(bool twoSided)
  {
    pimpl_->setTwoSided(twoSided);
  }

  [[nodiscard]] ShadingModel MaterialData::getShadingModel() const
  {
    return pimpl_->getShadingModel();
  }

  void MaterialData::setShadingModel(ShadingModel shadingModel)
  {
    pimpl_->setShadingModel(shadingModel);
  }

  [[nodiscard]] BlendMode MaterialData::getBlendMode() const
  {
    return pimpl_->getBlendMode();
  }

  void MaterialData::setBlendMode(BlendMode blendMode)
  {
    pimpl_->setBlendMode(blendMode);
  }

  [[nodiscard]] float MaterialData::getOpacity() const
  {
    return pimpl_->getOpacity();
  }

  void MaterialData::setOpacity(float opacity)
  {
    pimpl_->setOpacity(opacity);
  }

  [[nodiscard]] float MaterialData::getShininess() const
  {
    return pimpl_->getShininess();
  }

  void MaterialData::setShininess(float shininess)
  {
    pimpl_->setShininess(shininess);
  }

  [[nodiscard]] float MaterialData::getShininessStrength() const
  {
    return pimpl_->getShininessStrength();
  }

  void MaterialData::setShininessStrength(float shininessStrength)
  {
    pimpl_->setShininessStrength(shininessStrength);
  }

}  // namespace render