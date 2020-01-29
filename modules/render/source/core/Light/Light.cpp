#include "Light.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  // LightImpl --------------------------------------------------------------------------------------------------------

  LightImpl::LightImpl(vulkan::Device device)
      : buffer_(createUniformBuffer(device, nullptr, sizeof(ShaderLightData))),
        data_(buffer_.mapMemory(buffer_.getSize())),
        pData_(data_.pT<ShaderLightData>())
  {
  }

  void LightImpl::operator()(vulkan::CommandBuffer& commandBuffer) const
  {
    commandBuffer.bindBuffer(buffer_, vulkan::BindingInfo(7));
  }

  // Light ------------------------------------------------------------------------------------------------------------

  Light::Light(vulkan::Device const& device) : pimpl_(std::make_shared<LightImpl>(device))
  {
  }

  void Light::operator()(vulkan::CommandBuffer& commandBuffer) const
  {
    pimpl_->operator()(commandBuffer);
  }

  void Light::setPosition(glm::vec3 const& pos)
  {
    pimpl_->setPosition(pos);
  }

  [[nodiscard]] glm::vec3 Light::getPosition() const
  {
    return pimpl_->getPosition();
  }

  void Light::setIntensity(glm::vec3 intensity)
  {
    pimpl_->setIntensity(intensity);
  }

  [[nodiscard]] glm::vec3 Light::getIntensity() const
  {
    return pimpl_->getIntensity();
  }

}  // namespace render