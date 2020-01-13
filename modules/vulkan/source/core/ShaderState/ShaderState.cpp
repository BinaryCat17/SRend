#include "ShaderState.hpp"
#include "../Shader/Shader.hpp"

namespace vulkan
{
  // ShaderStateImpl --------------------------------------------------------------------------------------------------

  ShaderStateImpl::ShaderStateImpl(std::shared_ptr<DeviceImpl> device, ShaderStateCreateFlags const&)
      : device_(std::move(device))
  {
  }

  void ShaderStateImpl::addShader(Shader const& shader)
  {
    needUpdate_ = true;
    shaders_.push_back(ShaderInfo{shader});
  }

  void ShaderStateImpl::setShaderEntryPoint(utils::IndexT index, std::string const& name)
  {
    needUpdate_ = true;
    shaders_[index].entryPoint = name;
  }

  void ShaderStateImpl::setShaderSpecConstant(
      utils::IndexT index, utils::IndexT constantId, utils::SharedAnyPtr const& pData)
  {
    needUpdate_ = true;
    shaders_[index].specConstants.insert({constantId, pData});
  }

  void ShaderStateImpl::removeShader(utils::IndexT index)
  {
    needUpdate_ = true;
    shaders_.erase(shaders_.begin() + index);
  }

  void ShaderStateImpl::update()
  {
    std::vector<VezPipelineShaderStageCreateInfo> stages;

    if (needUpdate_)
    {
      stages.resize(shaders_.size());
      for (utils::IndexT i = 0; i != stages.size(); ++i)
      {
        stages[i].module = shaders_[i].shader.getImpl()->getVkShaderModule();
        stages[i].pEntryPoint = shaders_[i].entryPoint.data();
      }
    }

    VezGraphicsPipelineCreateInfo createInfo = {};
    createInfo.stageCount = static_cast<uint32_t>(stages.size());
    createInfo.pStages = stages.data();

    checkResult(vezCreateGraphicsPipeline(device_->getVkDevice(), &createInfo, &vkPipeline_));
  }

  // ShaderState ------------------------------------------------------------------------------------------------------

  void ShaderState::addShader(Shader const& shader)
  {
    pimpl_->addShader(shader);
  }

  void ShaderState::setShaderEntryPoint(utils::IndexT index, std::string const& name)
  {
    pimpl_->setShaderEntryPoint(index, name);
  }

  void ShaderState::setShaderSpecConstant(
      utils::IndexT index, utils::IndexT constantId, utils::SharedAnyPtr const& pData)
  {
    pimpl_->setShaderSpecConstant(index, constantId, pData);
  }

  void ShaderState::removeShader(utils::IndexT index)
  {
    pimpl_->removeShader(index);
  }

}  // namespace vulkan