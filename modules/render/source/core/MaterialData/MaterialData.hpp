#pragma once
#include <assimp/material.h>
#include "../utils.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  struct ShaderMaterialData
  {
    alignas(16) glm::vec3 diffuseColor = {};
    alignas(16) glm::vec3 specularColor = {};
    alignas(16) glm::vec3 ambientColor = {};
    alignas(16) glm::vec3 transparentColor = {};
    alignas(4) bool wireframe = {};
    alignas(4) bool twoSided = {};
    alignas(4) ShadingModel shadingModel = ShadingModel::Flat;
    alignas(4) BlendMode blendMode = BlendMode::Default;
    alignas(4) float opacity = {};
    alignas(4) float shininess = 60;
    alignas(4) float shininessStrength = 1;
  };

  // MaterialDataImpl -------------------------------------------------------------------------------------------------

  class MaterialDataImpl
  {
   public:
    explicit MaterialDataImpl(vulkan::Device device);

    explicit MaterialDataImpl(vulkan::Device device, aiMaterial const& aiMaterial);

    void operator()(vulkan::CommandBuffer& commandBuffer) const;

    [[nodiscard]] std::string const& getName() const
    {
      return name_;
    }

    void setName(std::string const& name)
    {
      name_ = name;
    }

    [[nodiscard]] glm::vec3 getDiffuseColor() const
    {
      return pData_->diffuseColor;
    }

    void setDiffuseColor(glm::vec3 const& diffuseColor)
    {
      pData_->diffuseColor = diffuseColor;
    }

    [[nodiscard]] glm::vec3 getSpecularColor() const
    {
      return pData_->specularColor;
    }

    void setSpecularColor(glm::vec3 const& specularColor)
    {
      pData_->specularColor = specularColor;
    }

    [[nodiscard]] glm::vec3 getAmbientColor() const
    {
      return pData_->ambientColor;
    }

    void setAmbientColor(glm::vec3 const& ambientColor)
    {
      pData_->ambientColor = ambientColor;
    }

    [[nodiscard]] glm::vec3 getTransparentColor() const
    {
      return pData_->transparentColor;
    }

    void setTransparentColor(glm::vec3 const& transparentColor)
    {
      pData_->transparentColor = transparentColor;
    }

    [[nodiscard]] bool isWireframe() const
    {
      return pData_->wireframe;
    }

    void setWireframe(bool wireframe)
    {
      pData_->wireframe = wireframe;
    }

    [[nodiscard]] bool isTwoSided() const
    {
      return pData_->twoSided;
    }

    void setTwoSided(bool twoSided)
    {
      pData_->twoSided = twoSided;
    }

    [[nodiscard]] ShadingModel getShadingModel() const
    {
      return pData_->shadingModel;
    }

    void setShadingModel(ShadingModel shadingModel)
    {
      pData_->shadingModel = shadingModel;
    }

    [[nodiscard]] BlendMode getBlendMode() const
    {
      return pData_->blendMode;
    }

    void setBlendMode(BlendMode blendMode)
    {
      pData_->blendMode = blendMode;
    }

    [[nodiscard]] float getOpacity() const
    {
      return pData_->opacity;
    }

    void setOpacity(float opacity)
    {
      pData_->opacity = opacity;
    }

    [[nodiscard]] float getShininess() const
    {
      return pData_->shininess;
    }

    void setShininess(float shininess)
    {
      pData_->shininess = shininess;
    }

    [[nodiscard]] float getShininessStrength() const
    {
      return pData_->shininessStrength;
    }

    void setShininessStrength(float shininessStrength)
    {
      pData_->shininessStrength = shininessStrength;
    }

   private:
    vulkan::Buffer buffer_;
    vulkan::BufferMappedData data_;
    ShaderMaterialData* pData_;
    std::string name_;
  };

}  // namespace render