#pragma once
#include "../utils.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  struct ShaderCameraData
  {
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
  };

  // CameraImpl -------------------------------------------------------------------------------------------------------

  class CameraImpl
  {
   public:
    explicit CameraImpl(vulkan::Device device, utils::Viewport viewport);

    void operator()(vulkan::CommandBuffer& commandBuffer) const;

    void setPosition(glm::vec3 const& pos);

    void setRotation(glm::vec3 const& pos);

    void setViewport(utils::Viewport const& viewport);

    [[nodiscard]] glm::vec3 getPosition() const
    {
      return pos_;
    }

    [[nodiscard]] glm::vec3 getRotation() const
    {
      return rotation_;
    }

    [[nodiscard]] vulkan::Viewport getViewport() const
    {
      return viewport_;
    }

    void setMovementSpeed(float val)
    {
      speed_ = val;
    }

    [[nodiscard]] float getMovementSpeed() const
    {
      return speed_;
    }

    void update();

   private:
    vulkan::Buffer buffer_;
    vulkan::BufferMappedData data_;
    vulkan::Viewport viewport_;
    glm::vec3 pos_ = {};
    glm::vec3 rotation_ = {};
    glm::vec3 front_ = glm::vec3(0, 0, 1);
    float speed_ = 1;
  };

}  // namespace render