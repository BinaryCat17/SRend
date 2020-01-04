#include "PipelineImpl.hpp"
#include "../Shader/ShaderImpl.hpp"

namespace vulkan
{
  // helpers
  // ----------------------------------------------------------------------------------------------

  size_t get_spec_size(std::vector<spec_const> const& infos)
  {
    size_t size = 0;
    for (auto const& info : infos)
    {
      size += info.size();
    }
    return size;
  }

  VezPipeline create_vk_pipeline(device device, std::vector<shader_module_info> const& modules)
  {
    std::vector<VezPipelineShaderStageCreateInfo> shaderStageInfos;
    for (auto const& Shader : modules)
    {
      size_t size = get_spec_size(Shader.infos_);
      std::unique_ptr<void, decltype(free)*> p_data(malloc(size), free);
      std::vector<vk::SpecializationMapEntry> spec_infos;

      uint32_t offset = 0;
      for (auto const& info : Shader.infos_)
      {
        spec_infos.emplace_back(info.id(), offset, info.size());
        memcpy(static_cast<char*>(p_data.get()) + offset, info.data(), info.size());
        offset += static_cast<uint32_t>(info.size());
      }

      vk::SpecializationInfo spec_info = {};
      spec_info.mapEntryCount = static_cast<uint32_t>(spec_infos.size());
      spec_info.pMapEntries = spec_infos.data();
      spec_info.pData = p_data.get();
      spec_info.dataSize = size;

      VezPipelineShaderStageCreateInfo shaderInfo = {};
      shaderInfo.module = Shader.shader_->get_vk_shader_module();
      shaderInfo.pEntryPoint = Shader.entry_point_.data();
      shaderInfo.pSpecializationInfo = nullptr;

      shaderStageInfos.push_back(shaderInfo);
    }

    VezGraphicsPipelineCreateInfo pipelineCreateInfo = {};
    pipelineCreateInfo.stageCount = static_cast<uint32_t>(shaderStageInfos.size());
    pipelineCreateInfo.pStages = shaderStageInfos.data();

    VezPipeline pipeline_;
    if (vezCreateGraphicsPipeline(device->get_vk_device(), &pipelineCreateInfo, &pipeline_) != VK_SUCCESS)
    {
      throw std::runtime_error("faield to create pipeline");
    }
    return pipeline_;
  }

  // impl
  // -------------------------------------------------------------------------------------------------

  pipeline_t::pipeline_t(device device, std::vector<shader_module_info> const& modules)
      : device_(device), vk_pipeline_(create_vk_pipeline(device, modules))
  {
  }
}  // namespace vulkan