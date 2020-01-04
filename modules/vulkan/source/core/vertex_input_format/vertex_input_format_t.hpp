#pragma once
#include "../Device/DeviceImpl.hpp"
#include "vertex_input_format.hpp"

namespace vulkan
{
  // vertex_input_format_t --------------------------------------------------------------------------------

  class vertex_input_format_t
  {
   public:
    vertex_input_format_t(device device, std::vector<vk::VertexInputAttributeDescription> const& attribute_descriptions,
        std::vector<vk::VertexInputBindingDescription> const& binding_descriptions);

    ~vertex_input_format_t()
    {
      vezDestroyVertexInputFormat(device_->get_vk_device(), vk_vertex_format_);
    }

    device get_device() const
    {
      return device_;
    }

    VezVertexInputFormat get_vk_vertex_format() const
    {
      return vk_vertex_format_;
    }

   private:
    device device_;
    VezVertexInputFormat vk_vertex_format_;
  };
}  // namespace vulkan