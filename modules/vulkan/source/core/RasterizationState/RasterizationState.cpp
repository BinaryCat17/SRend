#include "RasterizationState.hpp"
#include "../../../include/vulkan/core.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  // RasterizationStateImpl -------------------------------------------------------------------------------------------

  // RasterizationState -----------------------------------------------------------------------------------------------

  void RasterizationState::setDepthClamp(bool val) noexcept
  {
    pimpl_->setDepthClamp(val);
  }

  void RasterizationState::setRasterizerDiscard(bool val) noexcept
  {
    pimpl_->setRasterizerDiscard(val);
  }

  void RasterizationState::setDepthBias(bool val) noexcept
  {
    pimpl_->setDepthBias(val);
  }

  void RasterizationState::setPolygonMode(PolygonMode mode) noexcept
  {
    pimpl_->setPolygonMode(mode);
  }

  void RasterizationState::setCullMode(CullModeFlags const& cullMode) noexcept
  {
    pimpl_->setCullMode(cullMode);
  }

  void RasterizationState::setFrontFace(FrontFace frontFace) noexcept
  {
    pimpl_->setFrontFace(frontFace);
  }

  [[nodiscard]] bool RasterizationState::getDepthClamp() const noexcept
  {
    return pimpl_->getDepthClamp();
  }

  [[nodiscard]] bool RasterizationState::getRasterizerDiscard() const noexcept
  {
    return pimpl_->getRasterizerDiscard();
  }

  [[nodiscard]] bool RasterizationState::getDepthBias() const noexcept
  {
    return pimpl_->getDepthBias();
  }

  [[nodiscard]] PolygonMode RasterizationState::getPolygonMode() const noexcept
  {
    return pimpl_->getPolygonMode();
  }

  [[nodiscard]] CullModeFlags RasterizationState::getCullMode() const noexcept
  {
    return pimpl_->getCullMode();
  }

  [[nodiscard]] FrontFace RasterizationState::getFrontFace() const noexcept
  {
    return pimpl_->getFrontFace();
  }
  RasterizationState::RasterizationState(Device const& device, RasterizationStateCreateFlags const& createFlags)
      : pimpl_(std::make_shared<RasterizationStateImpl>(device.getImpl(), createFlags))
  {
  }

}  // namespace vulkan
