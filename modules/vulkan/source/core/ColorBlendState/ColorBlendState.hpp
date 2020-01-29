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

    void setLogicOp(std::optional<LogicOp> op) noexcept
    {
      state_.logicOpEnable = op.has_value();
      state_.logicOp = op.has_value() ? toVkLogicOp(*op) : VK_LOGIC_OP_AND;
    }

    [[nodiscard]] std::optional<LogicOp> getLogicOp() const noexcept
    {
      return state_.logicOpEnable ? static_cast<LogicOp>(state_.logicOp) : std::optional<LogicOp>();
    }

    void addAttachment(std::optional<ColorBlendAttachment> const& attachment,
        ColorComponentFlags colorWriteMask = ColorComponentFlagBits::R | ColorComponentFlagBits::G |
                                             ColorComponentFlagBits::B | ColorComponentFlagBits::A);

    void setAttachment(utils::IndexT index, std::optional<ColorBlendAttachment> const& attachment,
        ColorComponentFlags colorWriteMask = ColorComponentFlagBits::R | ColorComponentFlagBits::G |
                                             ColorComponentFlagBits::B | ColorComponentFlagBits::A);

    void removeAttachment(utils::IndexT index)
    {
      states_.erase(states_.begin() + index);
    }

    void update();

   private:
    std::vector<VezColorBlendAttachmentState> states_;
    VezColorBlendState state_ = {};
    bool needUpdate_ = true;
  };

}  // namespace vulkan