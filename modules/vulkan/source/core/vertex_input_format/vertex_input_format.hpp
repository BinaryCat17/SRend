#pragma once
#include "../Device/Device.hpp"
#include "../command_buffer/CommandBuffer.hpp"

namespace vulkan
{
  class vertex_input_format_t;
  using vertex_input_format = std::shared_ptr<vertex_input_format_t>;

  // vertex_format interface ------------------------------------------------------------------------------

  vertex_input_format create_vertex_input_description(device device,
      std::vector<vk::VertexInputAttributeDescription> const& attribute_descriptions,
      std::vector<vk::VertexInputBindingDescription> const& binding_descriptions);

  void cmd_set_vertex_format(command_buffer command_buffer, vertex_input_format vertex_format);
}  // namespace vulkan