#include "vertex_input_format_t.hpp"

namespace vulkan
{
  // helpers ----------------------------------------------------------------------------------------------

  VezVertexInputFormat create_vk_vertex_format(device device,
      std::vector<vk::VertexInputAttributeDescription> const& attribute_descriptions,
      std::vector<vk::VertexInputBindingDescription> const& binding_descriptions)
  {
    VezVertexInputFormatCreateInfo create_info = {};

    create_info.pVertexAttributeDescriptions =
        reinterpret_cast<VkVertexInputAttributeDescription const*>(attribute_descriptions.data());
    create_info.vertexAttributeDescriptionCount = static_cast<uint32_t>(attribute_descriptions.size());
    create_info.pVertexBindingDescriptions =
        reinterpret_cast<VkVertexInputBindingDescription const*>(binding_descriptions.data());
    create_info.vertexBindingDescriptionCount = static_cast<uint32_t>(binding_descriptions.size());

    VezVertexInputFormat result = nullptr;
    check_result(vezCreateVertexInputFormat(device->get_vk_device(), &create_info, &result));

    return result;
  }

  // vertex_input_format_t --------------------------------------------------------------------------------

  vertex_input_format_t::vertex_input_format_t(device device,
      std::vector<vk::VertexInputAttributeDescription> const& attribute_descriptions,
      std::vector<vk::VertexInputBindingDescription> const& binding_descriptions)
      : device_(device),
        vk_vertex_format_(create_vk_vertex_format(device, attribute_descriptions, binding_descriptions))
  {
  }
}  // namespace vulkan