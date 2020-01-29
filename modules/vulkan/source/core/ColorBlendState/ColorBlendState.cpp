#include "ColorBlendState.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  VezColorBlendAttachmentState createColorBlendAttachmentState(
      std::optional<ColorBlendAttachment> const& info, ColorComponentFlags colorWriteMask)
  {
    VezColorBlendAttachmentState state = {};
    state.colorWriteMask = toVkColorComponentFlags(colorWriteMask);
    state.blendEnable = info.has_value();
    if (info.has_value())
    {
      state.srcColorBlendFactor = toVkBlendFactor(info->srcColorBlendFactor);
      state.dstColorBlendFactor = toVkBlendFactor(info->dstColorBlendFactor);
      state.srcAlphaBlendFactor = toVkBlendFactor(info->srcAlphaBlendFactor);
      state.dstAlphaBlendFactor = toVkBlendFactor(info->dstAlphaBlendFactor);
      state.colorBlendOp = toVkBlendOp(info->colorBlendOp);
      state.alphaBlendOp = toVkBlendOp(info->alphaBlendOp);
    }
    return state;
  }

  // ColorBlendStateImpl ----------------------------------------------------------------------------------------------

  void ColorBlendStateImpl::addAttachment(
      std::optional<ColorBlendAttachment> const& attachment, ColorComponentFlags colorWriteMask)
  {
    states_.push_back(createColorBlendAttachmentState(attachment, colorWriteMask));
  }

  void ColorBlendStateImpl::setAttachment(
      utils::IndexT index, std::optional<ColorBlendAttachment> const& attachment, ColorComponentFlags colorWriteMask)
  {
    states_[index] = createColorBlendAttachmentState(attachment, colorWriteMask);
  }

  void ColorBlendStateImpl::update()
  {
    if (needUpdate_)
    {
      state_.attachmentCount = static_cast<uint32_t>(states_.size());
      state_.pAttachments = states_.data();
    }
    needUpdate_ = false;
  }

  // ColorBlendState --------------------------------------------------------------------------------------------------

  ColorBlendState::ColorBlendState(Device const& device, ColorBlendStateCreateFlags const& createFlags)
      : pimpl_(std::make_shared<ColorBlendStateImpl>(device.getImpl(), createFlags))
  {
  }

  void ColorBlendState::addAttachment(
      std::optional<ColorBlendAttachment> const& attachment, ColorComponentFlags colorWriteMask)
  {
    pimpl_->addAttachment(attachment, colorWriteMask);
  }

  void ColorBlendState::setAttachment(
      utils::IndexT index, std::optional<ColorBlendAttachment> const& attachment, ColorComponentFlags colorWriteMask)
  {
    pimpl_->setAttachment(index, attachment, colorWriteMask);
  }

  void ColorBlendState::removeAttachment(utils::IndexT index)
  {
    pimpl_->removeAttachment(index);
  }

  void ColorBlendState::setLogicOp(std::optional<LogicOp> val) noexcept
  {
    pimpl_->setLogicOp(val);
  }

  [[nodiscard]] std::optional<LogicOp> ColorBlendState::getLogicOp() const noexcept
  {
    return pimpl_->getLogicOp();
  }

}  // namespace vulkan