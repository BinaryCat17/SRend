#include "ColorBlendState.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  VkColorComponentFlags toVkColorComponentFlags(ColorComponentFlags flags)
  {
    return static_cast<VkColorComponentFlags>(flags);
  }

  VkBlendFactor toVkBlendFactor(BlendFactor val)
  {
    return static_cast<VkBlendFactor>(val);
  }

  VkBlendOp toVkBlendOp(BlendOp blendOp)
  {
    return static_cast<VkBlendOp>(blendOp);
  }

  VezColorBlendAttachmentState createColorBlendAttachmentState(
      std::optional<ColorBlendAttachmentInfo> const& info, ColorComponentFlags colorWriteMask)
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

  void ColorBlendStateImpl::addColorBlendAttachment(
      std::optional<ColorBlendAttachmentInfo> const& info, ColorComponentFlags colorWriteMask)
  {
    states_.push_back(createColorBlendAttachmentState(info, colorWriteMask));
  }

  void ColorBlendStateImpl::setColorBlendAttachment(
      utils::IndexT index, std::optional<ColorBlendAttachmentInfo> const& info, ColorComponentFlags colorWriteMask)
  {
    states_[index] = createColorBlendAttachmentState(info, colorWriteMask);
  }

  void ColorBlendStateImpl::removeColorBlendAttachment(utils::IndexT index)
  {
    states_.erase(states_.begin() + index);
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

  void ColorBlendState::addColorBlendAttachment(
      std::optional<ColorBlendAttachmentInfo> const& info, ColorComponentFlags colorWriteMask)
  {
    pimpl_->addColorBlendAttachment(info, colorWriteMask);
  }

  void ColorBlendState::setColorBlendAttachment(
      utils::IndexT index, std::optional<ColorBlendAttachmentInfo> const& info, ColorComponentFlags colorWriteMask)
  {
    pimpl_->setColorBlendAttachment(index, info, colorWriteMask);
  }

  void ColorBlendState::removeColorBlendAttachment(utils::IndexT index)
  {
    pimpl_->removeColorBlendAttachment(index);
  }

}  // namespace vulkan