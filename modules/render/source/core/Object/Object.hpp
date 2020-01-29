#pragma once
#include "../utils.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  struct ObjectData
  {
    glm::mat4 transform = glm::mat4(1);
  };

  // ObjectImpl -------------------------------------------------------------------------------------------------------

  class ObjectImpl
  {
   public:
    explicit ObjectImpl(vulkan::Device device, Mesh mesh, Material material);

    void operator()(vulkan::CommandBuffer& commandBuffer) const;

    [[nodiscard]] Mesh getMesh() const
    {
      return mesh_;
    }

    [[nodiscard]] Material getMaterial() const
    {
      return material_;
    }

    void setPosition(glm::vec3 const& pos);

    void setRotation(glm::vec3 const& rotation);

    void setScale(glm::vec3 const& scale);

    [[nodiscard]] glm::vec3 getPosition() const
    {
      return position_;
    }

    [[nodiscard]] glm::vec3 getRotation() const
    {
      return rotation_;
    }

    [[nodiscard]] glm::vec3 getScale() const
    {
      return scale_;
    }

    void translate(glm::vec3 const& pos);

    void rotate(glm::vec3 const& rotation);

    void scale(glm::vec3 const& scale);

    [[nodiscard]] glm::mat4 getTransform() const
    {
      return transform_;
    }

    [[nodiscard]] std::string getName() const
    {
      return name_;
    }

    void setParentTransform(glm::mat4 const& parentTransform)
    {
      parentTransform_ = parentTransform;
      update();
    }

    [[nodiscard]] glm::mat4 const& getParentTransform() const
    {
      return parentTransform_;
    }

   private:
    void update();

    Mesh mesh_;
    Material material_;
    ObjectData data_;
    vulkan::Buffer uniformBuffer_;
    glm::vec3 position_ = {};
    glm::vec3 rotation_ = {};
    glm::vec3 scale_= glm::vec3(1);
    std::string name_;
    glm::mat4 transform_ = glm::mat4(1);
    glm::mat4 parentTransform_ = glm::mat4(1);
  };

}  // namespace render