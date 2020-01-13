#include "MultisampleState.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  // MultisampleStateImpl ---------------------------------------------------------------------------------------------

  // MultisampleState -------------------------------------------------------------------------------------------------

  void MultisampleState::setRasterizationSamples(SampleCountFlagBits sampleCount)
  {
    pimpl_->setRasterizationSamples(sampleCount);
  }

  void MultisampleState::enableSampleShading(float minSampleShading)
  {
    pimpl_->enableSampleShading(minSampleShading);
  }

  void MultisampleState::disableSampleShading()
  {
    pimpl_->disableSampleShading();
  }

  void MultisampleState::setSampleMask(uint32_t mask)
  {
    pimpl_->setSampleMask(mask);
  }

  void MultisampleState::enableAlphaToCoverage()
  {
    pimpl_->enableAlphaToCoverage();
  }

  void MultisampleState::disableAlphaToCoverage()
  {
    pimpl_->disableAlphaToCoverage();
  }

  void MultisampleState::enableAlphaToOne()
  {
    pimpl_->enableAlphaToOne();
  }

  void MultisampleState::disableAlphaToOne()
  {
    pimpl_->disableAlphaToOne();
  }

}  // namespace vulkan