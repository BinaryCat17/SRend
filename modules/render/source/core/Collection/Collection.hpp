#pragma once
#include "../utils.hpp"
#include <set>

namespace render
{
  // CollectionImpl ---------------------------------------------------------------------------------------------------

  class CollectionImpl
  {
   public:
    explicit CollectionImpl(std::string name) : name_(std::move(name))
    {

    }

    void operator()(vulkan::CommandBuffer& commandBuffer) const;

    [[nodiscard]] std::string getName() const
    {
      return name_;
    }

    [[nodiscard]] utils::SizeT size() const
    {
      return members_.size();
    }

    void insert(std::variant<Object, Collection> const& obj);

    void erase(std::variant<Object, Collection> const& obj)
    {
      members_.erase(obj);
    }

    [[nodiscard]] Collection::iterator begin()
    {
      return members_.begin();
    }

    [[nodiscard]] Collection::const_iterator begin() const
    {
      return members_.cbegin();
    }

    [[nodiscard]] Collection::iterator end()
    {
      return members_.end();
    }

    [[nodiscard]] Collection::const_iterator end() const
    {
      return members_.cend();
    }

    void setPosition(glm::vec3 pos);

    void setRotation(glm::vec3 rotation);

    void setScale(glm::vec3 scale);

    void translate(glm::vec3 const& pos);

    void rotate(glm::vec3 const& rotation);

    void scale(glm::vec3 const& scale);

    [[nodiscard]] glm::vec3 const& getPosition() const
    {
      return position_;
    }

    [[nodiscard]] glm::vec3 const& getRotation() const
    {
      return rotation_;
    }

    [[nodiscard]] glm::vec3 const& getScale() const
    {
      return scale_;
    }

    [[nodiscard]] glm::mat4 getTransform() const
    {
      return transform_;
    }

    void setParentTransform(glm::mat4 const& parentTransform)
    {
      parentTransform_ = parentTransform;
    }

    [[nodiscard]] glm::mat4 const& getParentTransform() const
    {
      return parentTransform_;
    }

   private:
    std::set<std::variant<Object, Collection>> members_;
    std::string name_;
    glm::vec3 position_ = glm::vec3(0);
    glm::vec3 rotation_ = glm::vec3(0);
    glm::vec3 scale_ = glm::vec3(1);
    glm::mat4 transform_ = glm::mat4(1);
    glm::mat4 parentTransform_ = glm::mat4(1);
  };

}  // namespace render