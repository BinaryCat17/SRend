#pragma once
#include <map>
#include "../Device/Device.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  struct InputAttributeInfo
  {
    Format format = {};
    utils::OffsetT offset = {};
  };

  struct InputBindingInfo
  {
    VertexInputRate rate = {};
    utils::SizeT stride = {};
    std::map<utils::IndexT, InputAttributeInfo> attributes = {};
    utils::IndexT currentLocation_ = std::numeric_limits<utils::IndexT>::max();
  };

  // VertexInputStateImpl ---------------------------------------------------------------------------------------------

  class VertexInputStateImpl
  {
   public:
    explicit VertexInputStateImpl(std::shared_ptr<DeviceImpl> device, VertexInputStateCreateFlags const& createFlags);

    VertexInputStateImpl(VertexInputStateImpl const&) = delete;

    VertexInputStateImpl(VertexInputStateImpl&&) = delete;

    VertexInputStateImpl& operator=(VertexInputStateImpl const&) = delete;

    VertexInputStateImpl& operator=(VertexInputStateImpl&&) = delete;

    [[nodiscard]] VezVertexInputFormat getVkVertexInputFormat() const
    {
      return vkVertexInputFormat_;
    }

    void addInputBinding(VertexInputRate rate);

    void addInputBinding(utils::SizeT stride, VertexInputRate rate);

    void addInputAttribute(Format format);

    void addInputAttribute(Format format, utils::OffsetT offset);

    void addInputAttribute(utils::IndexT binding, Format format, utils::OffsetT offset);

    void setInputBinding(utils::IndexT binding, utils::SizeT stride, VertexInputRate rate);

    void setInputAttribute(utils::IndexT binding, utils::IndexT location, Format format, utils::OffsetT offset);

    void eraseInputBinding(utils::IndexT binding);

    void eraseInputAttribute(utils::IndexT binding, utils::IndexT location);

    void update();

   private:
    std::shared_ptr<DeviceImpl> device_;
    std::map<utils::IndexT, InputBindingInfo> inputInfo_;
    utils::IndexT currentBinding_ = std::numeric_limits<utils::IndexT>::max();
    VezVertexInputFormat vkVertexInputFormat_ = nullptr;
    bool needUpdate_ = true;
  };

}  // namespace vulkan