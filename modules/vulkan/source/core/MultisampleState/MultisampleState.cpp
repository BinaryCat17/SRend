#include "MultisampleState.hpp"
#include "../../../include/vulkan/core.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  // MultisampleStateImpl ---------------------------------------------------------------------------------------------

  // MultisampleState -------------------------------------------------------------------------------------------------

  void MultisampleState::setRasterizationSamples(SampleCountFlagBits val) noexcept
  {
    pimpl_->setRasterizationSamples(val);
  }

  void MultisampleState::setSampleShading(std::optional<float> val) noexcept
  {
    pimpl_->setSampleShading(val);
  }

  void MultisampleState::setSampleMask(uint32_t val) noexcept
  {
    pimpl_->setSampleMask(val);
  }

  void MultisampleState::setAlphaToCoverage(bool val) noexcept
  {
    pimpl_->setAlphaToCoverage(val);
  }

  void MultisampleState::setAlphaToOne(bool val) noexcept
  {
    pimpl_->setAlphaToOne(val);
  }

  [[nodiscard]] SampleCountFlagBits MultisampleState::getRasterizationSamples() const noexcept
  {
    return pimpl_->getRasterizationSamples();
  }

  [[nodiscard]] std::optional<float> MultisampleState::getSampleShading() const noexcept
  {
    return pimpl_->getSampleShading();
  }

  [[nodiscard]] uint32_t MultisampleState::getSampleMask() const noexcept
  {
    return pimpl_->getSampleMask();
  }

  [[nodiscard]] bool MultisampleState::getAlphaToCoverage() const noexcept
  {
    return pimpl_->getAlphaToCoverage();
  }

  [[nodiscard]] bool MultisampleState::getAlphaToOne() const noexcept
  {
    return pimpl_->getAlphaToOne();
  }

  MultisampleState::MultisampleState(Device const& device, MultisampleStateCreateFlags const& createFlags)
      : pimpl_(std::make_shared<MultisampleStateImpl>(device.getImpl(), createFlags))
  {
  }

}  // namespace vulkan