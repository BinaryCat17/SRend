#include "Collection.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../../../include/render/core.hpp"
#include "../Object/Object.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  void recurseSetParentMatrix(
      render::Collection::iterator begin, render::Collection::iterator end, glm::mat4 const& transform)
  {
    for (; begin != end; ++begin)
    {
      std::visit(
          [&transform]<typename T>(T val) {
            val.getImpl()->setParentTransform(transform);

            if constexpr (std::is_same_v<T, render::Collection>)
            {
              recurseSetParentMatrix(val.begin(), val.end(), val.getTransform() * transform);
            }
          },
          *begin);
    }
  }

  // CollectionImpl ---------------------------------------------------------------------------------------------------

  void CollectionImpl::operator()(vulkan::CommandBuffer& commandBuffer) const
  {
    for (auto const& member : members_)
    {
      std::visit(
          [&commandBuffer]<typename T>(T const& val) { val(commandBuffer); }, member);
    }
  }

  void CollectionImpl::setPosition(glm::vec3 pos)
  {
    position_ = pos;
    transform_ = createTransformMatrix(position_, rotation_, scale_);
    recurseSetParentMatrix(members_.begin(), members_.end(), parentTransform_ * getTransform());
  }

  void CollectionImpl::setRotation(glm::vec3 rotation)
  {
    rotation_ = rotation;
    transform_ = createTransformMatrix(position_, rotation_, scale_);
    recurseSetParentMatrix(members_.begin(), members_.end(), parentTransform_ * getTransform());
  }

  void CollectionImpl::setScale(glm::vec3 scale)
  {
    scale_ = scale;
    transform_ = createTransformMatrix(position_, rotation_, scale_);
    recurseSetParentMatrix(members_.begin(), members_.end(), parentTransform_ * getTransform());
  }

  void CollectionImpl::translate(glm::vec3 const& pos)
  {
    position_ += pos;
    glm::translate(transform_, pos);
  }

  void CollectionImpl::rotate(glm::vec3 const& rotation)
  {
    rotation_ += rotation;
    glm::rotate(transform_, glm::radians(rotation.x), glm::vec3(1,0,0));
    glm::rotate(transform_, glm::radians(rotation.y), glm::vec3(0,1,0));
    glm::rotate(transform_, glm::radians(rotation.z), glm::vec3(0,0,1));
  }

  void CollectionImpl::scale(glm::vec3 const& scale)
  {
    scale_ += scale;
    glm::translate(transform_, scale);
  }

  void CollectionImpl::insert(std::variant<Object, Collection> const& obj)
  {
    std::visit([this](auto&& val) { val.getImpl()->setParentTransform(transform_); }, obj);
    members_.insert(obj);
  }

  // Collection -------------------------------------------------------------------------------------------------------

  Collection::Collection(vulkan::Device const&, std::string const& name)
      : pimpl_(std::make_shared<CollectionImpl>(name))
  {
  }

  void Collection::operator()(vulkan::CommandBuffer& commandBuffer) const
  {
    pimpl_->operator()(commandBuffer);
  }

  [[nodiscard]] utils::SizeT Collection::size() const
  {
    return pimpl_->size();
  }

  void Collection::insert(std::variant<Object, Collection> const& obj)
  {
    pimpl_->insert(obj);
  }

  void Collection::erase(std::variant<Object, Collection> const& obj)
  {
    pimpl_->erase(obj);
  }

  [[nodiscard]] Collection::iterator Collection::begin()
  {
    return pimpl_->begin();
  }

  [[nodiscard]] Collection::const_iterator Collection::begin() const
  {
    return pimpl_->begin();
  }

  [[nodiscard]] Collection::iterator Collection::end()
  {
    return pimpl_->end();
  }

  [[nodiscard]] Collection::const_iterator Collection::end() const
  {
    return pimpl_->end();
  }

  std::string Collection::getName() const
  {
    return pimpl_->getName();
  }

  void Collection::setPosition(glm::vec3 pos)
  {
    pimpl_->setPosition(pos);
  }

  void Collection::setRotation(glm::vec3 rotation)
  {
    pimpl_->setRotation(rotation);
  }

  void Collection::setScale(glm::vec3 scale)
  {
    pimpl_->setScale(scale);
  }
  void Collection::translate(glm::vec3 const& pos)
  {
    pimpl_->translate(pos);
  }

  void Collection::rotate(glm::vec3 const& rotation)
  {
    pimpl_->rotate(rotation);
  }

  void Collection::scale(glm::vec3 const& scale)
  {
    pimpl_->scale(scale);
  }

  glm::mat4 Collection::getTransform() const
  {
    return pimpl_->getTransform();
  }

  glm::vec3 Collection::getPosition() const
  {
    return pimpl_->getPosition();
  }

  glm::vec3 Collection::getRotation() const
  {
    return pimpl_->getRotation();
  }

  glm::vec3 Collection::getScale() const
  {
    return pimpl_->getScale();
  }

}  // namespace render