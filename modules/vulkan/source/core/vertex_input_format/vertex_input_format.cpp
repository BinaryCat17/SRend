#include "vertex_input_format_t.hpp"

namespace vulkan
{
  vertex_input_format create_vertex_input_description(device device,
      std::vector<vk::VertexInputAttributeDescription> const& attribute_descriptions,
      std::vector<vk::VertexInputBindingDescription> const& binding_descriptions)
  {
    return std::make_shared<vertex_input_format_t>(device, attribute_descriptions, binding_descriptions);
  }

  void cmd_set_vertex_format(command_buffer, vertex_input_format vertex_format)
  {
    vezCmdSetVertexInputFormat(vertex_format->get_vk_vertex_format());
  }
}  // namespace vulkan
