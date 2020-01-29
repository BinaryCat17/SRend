#include "Object.hpp"
#include "../Material/Material.hpp"
#include "../Mesh/Mesh.hpp"
#include "../../../include/render/core.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  // ObjectImpl -------------------------------------------------------------------------------------------------------

  ObjectImpl::ObjectImpl(vulkan::Device device, Mesh mesh, Material material)
      : mesh_(std::move(mesh)),
        material_(std::move(material)),
        uniformBuffer_(createUniformBuffer(device, &data_, sizeof(ObjectData))),
        name_(mesh_.getName())
  {
  }

  void ObjectImpl::operator()(vulkan::CommandBuffer& commandBuffer) const
  {
    commandBuffer.bindBuffer(uniformBuffer_, vulkan::BindingInfo(8));
    (*material_.getImpl())(commandBuffer);
    (*mesh_.getImpl())(commandBuffer);
  }

  void ObjectImpl::setPosition(glm::vec3 const& pos)
  {
    position_ = pos;
    update();
  }

  void ObjectImpl::setRotation(glm::vec3 const& rotation)
  {
    rotation_ = rotation;
    update();
  }

  void ObjectImpl::setScale(glm::vec3 const& scale)
  {
    scale_ = scale;
    update();
  }

  void ObjectImpl::update()
  {
    transform_ = createTransformMatrix(position_, rotation_, scale_);
    data_.transform = parentTransform_ * transform_ ;
    memCopyToBuffer(uniformBuffer_, &data_, sizeof(ObjectData));
  }

  void ObjectImpl::translate(glm::vec3 const& pos)
  {
    position_ += pos;
    update();
  }

  void ObjectImpl::rotate(glm::vec3 const& rotation)
  {
    rotation_ += rotation;
    update();
  }

  void ObjectImpl::scale(glm::vec3 const& scale)
  {
    scale_ += scale;
    update();
  }

  // Object -----------------------------------------------------------------------------------------------------------

  Object::Object(vulkan::Device const& device, Mesh const& mesh, Material const& material)
      : pimpl_(std::make_shared<ObjectImpl>(device, mesh, material))
  {
  }

  void Object::operator()(vulkan::CommandBuffer& commandBuffer) const
  {
    pimpl_->operator()(commandBuffer);
  }

  [[nodiscard]] Mesh Object::getMesh() const
  {
    return pimpl_->getMesh();
  }

  [[nodiscard]] Material Object::getMaterial() const
  {
    return pimpl_->getMaterial();
  }

  void Object::setPosition(glm::vec3 const& pos)
  {
    pimpl_->setPosition(pos);
  }

  void Object::setRotation(glm::vec3 const& val)
  {
    pimpl_->setRotation(val);
  }

  void Object::setScale(glm::vec3 const& scale)
  {
    pimpl_->setScale(scale);
  }

  [[nodiscard]] glm::vec3 Object::getPosition() const
  {
    return pimpl_->getPosition();
  }

  [[nodiscard]] glm::vec3 Object::getRotation() const
  {
    return pimpl_->getRotation();
  }

  [[nodiscard]] glm::vec3 Object::getScale() const
  {
    return pimpl_->getScale();
  }

  std::string Object::getName() const
  {
    return pimpl_->getName();
  }

  void Object::translate(glm::vec3 const& pos)
  {
    pimpl_->translate(pos);
  }

  void Object::rotate(glm::vec3 const& rotation)
  {
    pimpl_->rotate(rotation);
  }

  void Object::scale(glm::vec3 const& scale)
  {
    pimpl_->scale(scale);
  }

  glm::mat4 Object::getTransform() const
  {
    return glm::mat4();
  }

}  // namespace render