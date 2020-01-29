#pragma once
#include "../utils.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  struct ShaderLightData
  {
    alignas(16) glm::vec3 pos;
    alignas(16) glm::vec3 intensity;
  };

  // LightImpl --------------------------------------------------------------------------------------------------------

  class LightImpl
  {
   public:
    explicit LightImpl(vulkan::Device device);

    void operator()(vulkan::CommandBuffer& commandBuffer) const;

    void setPosition(glm::vec3 const& pos)
    {
      pData_->pos = pos;
    }

    [[nodiscard]] glm::vec3 getPosition() const
    {
      return pData_->pos;
    }

    void setIntensity(glm::vec3 intensity)
    {
      pData_->intensity = intensity;
    }

    [[nodiscard]] glm::vec3 getIntensity() const
    {
      return pData_->intensity;
    }

   private:
    vulkan::Buffer buffer_;
    vulkan::BufferMappedData data_;
    ShaderLightData* pData_;
  };

}  // namespace render