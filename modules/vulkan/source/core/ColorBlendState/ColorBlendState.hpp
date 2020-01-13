#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // ColorBlendStateImpl ----------------------------------------------------------------------------------------------

  class ColorBlendStateImpl
  {
   public:
    explicit ColorBlendStateImpl(std::shared_ptr<DeviceImpl> const&, ColorBlendStateCreateFlags const&)
    {
    }

    ColorBlendStateImpl(ColorBlendStateImpl const&) = delete;

    ColorBlendStateImpl(ColorBlendStateImpl&&) = delete;

    ColorBlendStateImpl& operator=(ColorBlendStateImpl const&) = delete;

    ColorBlendStateImpl& operator=(ColorBlendStateImpl&&) = delete;

    [[nodiscard]] VezColorBlendState const& getVkColorBlendState() const
    {
      return state_;
    }

    void enableLogicOp(LogicOp op)
    {
      state_.logicOpEnable = true;
      state_.logicOp = static_cast<VkLogicOp>(toVkLogicOp(op));
    }

    void disableLogicOp()
    {
      state_.logicOpEnable = false;
    }

    void addColorBlendAttachment(
        std::optional<ColorBlendAttachmentInfo> const& info, ColorComponentFlags colorWriteMask);

    void setColorBlendAttachment(
        utils::IndexT index, std::optional<ColorBlendAttachmentInfo> const& info, ColorComponentFlags colorWriteMask);

    void removeColorBlendAttachment(utils::IndexT index);

    void update();

   private:
    std::vector<VezColorBlendAttachmentState> states_;
    VezColorBlendState state_ = {};
    bool needUpdate_ = true;
  };

}  // namespace vulkan