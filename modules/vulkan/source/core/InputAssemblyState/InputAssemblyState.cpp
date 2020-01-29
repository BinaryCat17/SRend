#include "InputAssemblyState.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  vk::PrimitiveTopology toVkPrimitiveTopology(PrimitiveTopology topology)
  {
    return static_cast<vk::PrimitiveTopology>(topology);
  }

  // InputAssemblyStateImpl -------------------------------------------------------------------------------------------

  // InputAssemblyState -----------------------------------------------------------------------------------------------

  void InputAssemblyState::setPrimitiveTopology(PrimitiveTopology topology) noexcept
  {
    pimpl_->setPrimitiveTopology(topology);
  }

  void InputAssemblyState::setPrimitiveRestart(bool val) noexcept
  {
    pimpl_->setPrimitiveRestart(val);
  }

  [[nodiscard]] PrimitiveTopology InputAssemblyState::getPrimitiveTopology() const noexcept
  {
    return pimpl_->getPrimitiveTopology();
  }

  [[nodiscard]] bool InputAssemblyState::getPrimitiveRestart() const noexcept
  {
    return pimpl_->getPrimitiveRestart();
  }
  InputAssemblyState::InputAssemblyState(Device const& device, InputAssemblyStateCreateFlags const& createFlags)
      : pimpl_(std::make_shared<InputAssemblyStateImpl>(device.getImpl(), createFlags))
  {
  }

}  // namespace vulkan