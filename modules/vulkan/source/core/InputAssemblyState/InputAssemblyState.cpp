#include "InputAssemblyState.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  vk::PrimitiveTopology toVkPrimitiveTopology(PrimitiveTopology topology)
  {
    return static_cast<vk::PrimitiveTopology>(topology);
  }

  // InputAssemblyStateImpl -------------------------------------------------------------------------------------------

  void InputAssemblyStateImpl::setPrimitiveTopology(PrimitiveTopology topology)
  {
    vkInputAssemblyState_.topology = static_cast<VkPrimitiveTopology>(toVkPrimitiveTopology(topology));
  }

  // InputAssemblyState -----------------------------------------------------------------------------------------------

  void InputAssemblyState::setPrimitiveTopology(PrimitiveTopology topology)
  {
    pimpl_->setPrimitiveTopology(topology);
  }

  void InputAssemblyState::enablePrimitiveRestart()
  {
    pimpl_->enablePrimitiveRestart();
  }

  void InputAssemblyState::disablePrimitiveRestart()
  {
    pimpl_->disablePrimitiveRestart();
  }

}  // namespace vulkan