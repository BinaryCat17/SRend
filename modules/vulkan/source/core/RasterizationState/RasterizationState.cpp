#include "RasterizationState.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  vk::PolygonMode toVkPolygonMode(PolygonMode mode)
  {
    return static_cast<vk::PolygonMode>(mode);
  }

  vk::CullModeFlags toVkCullModeFlags(CullModeFlags const& cullMode)
  {
    return static_cast<vk::CullModeFlags>(static_cast<VkCullModeFlags>(cullMode));
  }

  vk::FrontFace toVkFrontFace(FrontFace frontFace)
  {
    return static_cast<vk::FrontFace>(frontFace);
  }

  // RasterizationStateImpl -------------------------------------------------------------------------------------------

  void RasterizationStateImpl::setPolygonMode(PolygonMode mode)
  {
    rasterizationState_.polygonMode = static_cast<VkPolygonMode>(toVkPolygonMode(mode));
  }

  void RasterizationStateImpl::setCullMode(CullModeFlags const& cullMode)
  {
    rasterizationState_.cullMode = static_cast<VkCullModeFlags>(toVkCullModeFlags(cullMode));
  }

  void RasterizationStateImpl::setFrontFace(FrontFace frontFace)
  {
    rasterizationState_.frontFace = static_cast<VkFrontFace>(toVkFrontFace(frontFace));
  }

  // RasterizationState -----------------------------------------------------------------------------------------------

  void RasterizationState::enableDepthClamp()
  {
    pimpl_->enableDepthClamp();
  }

  void RasterizationState::disableDepthClamp()
  {
    pimpl_->disableDepthClamp();
  }

  void RasterizationState::enableRasterizerDiscard()
  {
    pimpl_->enableRasterizerDiscard();
  }

  void RasterizationState::disableRasterizerDiscard()
  {
    pimpl_->disableRasterizerDiscard();
  }

  void RasterizationState::enableDepthBias()
  {
    pimpl_->enableDepthBias();
  }

  void RasterizationState::disableDepthBias()
  {
    pimpl_->disableDepthBias();
  }

  void RasterizationState::setPolygonMode(PolygonMode mode)
  {
    pimpl_->setPolygonMode(mode);
  }

  void RasterizationState::setCullMode(CullModeFlags const& cullMode)
  {
    pimpl_->setCullMode(cullMode);
  }

  void RasterizationState::setFrontFace(FrontFace frontFace)
  {
    pimpl_->setFrontFace(frontFace);
  }

}  // namespace vulkan
