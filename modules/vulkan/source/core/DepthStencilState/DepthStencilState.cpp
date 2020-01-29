#include "DepthStencilState.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  VezStencilOpState toVkStencilOpState(StencilOpInfo const& state)
  {
    VezStencilOpState vkState = {};
    vkState.compareOp = static_cast<VkCompareOp>(state.compareOp);
    vkState.depthFailOp = static_cast<VkStencilOp>(state.depthFailOp);
    vkState.passOp = static_cast<VkStencilOp>(state.passOp);
    vkState.failOp = static_cast<VkStencilOp>(state.failOp);

    return vkState;
  }

  // ViewportStateImpl ------------------------------------------------------------------------------------------------

  void DepthStencilStateImpl::setBackStencilOp(StencilOpInfo const& state)
  {
    vkDepthStencilState_.back = toVkStencilOpState(state);
  }

  void DepthStencilStateImpl::setFrontStencilOp(StencilOpInfo const& state)
  {
    vkDepthStencilState_.front = toVkStencilOpState(state);
  }

  // ViewportState ----------------------------------------------------------------------------------------------------

  DepthStencilState::DepthStencilState(Device const& device, DepthStencilStateCreateFlags const& createFlags)
      : pimpl_(std::make_shared<DepthStencilStateImpl>(device.getImpl(), createFlags))
  {
  }

  void DepthStencilState::setDepthTest(bool val) noexcept
  {
    pimpl_->setDepthTest(val);
  }

  void DepthStencilState::setDepthWrite(bool val) noexcept
  {
    pimpl_->setDepthWrite(val);
  }

  void DepthStencilState::setDepthCompareOp(CompareOp val) noexcept
  {
    pimpl_->setDepthCompareOp(val);
  }

  void DepthStencilState::setDepthBoundsTest(bool val) noexcept
  {
    pimpl_->setDepthBoundsTest(val);
  }

  void DepthStencilState::setBackStencilOp(StencilOpInfo const& val) noexcept
  {
    pimpl_->setBackStencilOp(val);
  }

  void DepthStencilState::setFrontStencilOp(StencilOpInfo const& val) noexcept
  {
    pimpl_->setFrontStencilOp(val);
  }

  [[nodiscard]] bool DepthStencilState::getDepthTest() const noexcept
  {
    return pimpl_->getDepthTest();
  }

  [[nodiscard]] bool DepthStencilState::getDepthWrite() const noexcept
  {
    return pimpl_->getDepthWrite();
  }

  [[nodiscard]] CompareOp DepthStencilState::getDepthCompareOp() const noexcept
  {
    return pimpl_->getDepthCompareOp();
  }

  [[nodiscard]] bool DepthStencilState::getDepthBoundsTest() const noexcept
  {
    return pimpl_->getDepthBoundsTest();
  }

  [[nodiscard]] StencilOpInfo DepthStencilState::getBackStencilOp() const noexcept
  {
    return pimpl_->getBackStencilOp();
  }

  [[nodiscard]] StencilOpInfo DepthStencilState::getFrontStencilOp() const noexcept
  {
    return pimpl_->getFrontStencilOp();
  }

}  // namespace vulkan