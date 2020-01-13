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

  void DepthStencilState::enableDepthTest()
  {
    pimpl_->enableDepthTest();
  }

  void DepthStencilState::disableDepthTest()
  {
    pimpl_->disableDepthTest();
  }

  void DepthStencilState::enableDepthWrite()
  {
    pimpl_->enableDepthWrite();
  }

  void DepthStencilState::disableDepthWrite()
  {
    pimpl_->disableDepthWrite();
  }

  void DepthStencilState::setDepthCompareOp(CompareOp op)
  {
    pimpl_->setDepthCompareOp(op);
  }

  void DepthStencilState::enableDepthBoundsTest()
  {
    pimpl_->enableDepthBoundsTest();
  }

  void DepthStencilState::disableDepthBoundsTest()
  {
    pimpl_->disableDepthBoundsTest();
  }

  void DepthStencilState::setBackStencilOp(StencilOpInfo const& state)
  {
    pimpl_->setBackStencilOp(state);
  }

  void DepthStencilState::setFrontStencilOp(StencilOpInfo const& state)
  {
    pimpl_->setFrontStencilOp(state);
  }

}  // namespace vulkan