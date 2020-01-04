#include "PipelineImpl.hpp"

namespace vulkan
{
  // pipeline ----------------------------------------------------------------------------------------------

  pipeline create_pipeline(device device, std::vector<shader_module_info> const& shader_modules)
  {
    return std::make_shared<pipeline_t>(device, shader_modules);
  }

  void cmd_bind(command_buffer, pipeline pipeline)
  {
    vezCmdBindPipeline(pipeline->get_vk_pipeline());
  }
}  // namespace vulkan