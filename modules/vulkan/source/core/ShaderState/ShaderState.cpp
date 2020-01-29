#include "ShaderState.hpp"
#include "../Shader/Shader.hpp"

namespace vulkan
{
  // ShaderStateImpl --------------------------------------------------------------------------------------------------

  ShaderStateImpl::ShaderStateImpl(std::shared_ptr<DeviceImpl> device, ShaderStateCreateFlags const&)
      : device_(std::move(device))
  {
  }

  ShaderStateImpl::~ShaderStateImpl()
  {
    vezDestroyPipeline(device_->getVkDevice(), vkPipeline_);
  }

  void ShaderStateImpl::addShader(Shader const& shader)
  {
    needUpdate_ = true;
    shaders_.insert({shader, ShaderInfo()});
  }

  void ShaderStateImpl::setEntryPoint(Shader const& shader, std::string const& name)
  {
    needUpdate_ = true;
    shaders_.at(shader).entryPoint = name;
  }

  std::string ShaderStateImpl::getEntryPoint(Shader const& shader) const
  {
    return shaders_.at(shader).entryPoint;
  }

  void ShaderStateImpl::update()
  {
    if (needUpdate_)
    {
      std::vector<VezPipelineShaderStageCreateInfo> stages;
      for (auto const& p : shaders_)
      {
        VezPipelineShaderStageCreateInfo createInfo = {};

        createInfo.module = p.first.getImpl()->getVkShaderModule();
        createInfo.pEntryPoint = p.second.entryPoint.data();

        stages.push_back(createInfo);
      }

      VezGraphicsPipelineCreateInfo createInfo = {};
      createInfo.stageCount = static_cast<uint32_t>(stages.size());
      createInfo.pStages = stages.data();

      checkResult(vezCreateGraphicsPipeline(device_->getVkDevice(), &createInfo, &vkPipeline_));
    }
    needUpdate_ = false;
  }

  // ShaderState ------------------------------------------------------------------------------------------------------

  ShaderState::ShaderState(Device const& device, ShaderStateCreateFlags const& createFlags)
      : pimpl_(std::make_shared<ShaderStateImpl>(device.getImpl(), createFlags))
  {
  }

  void ShaderState::addShader(Shader const& shader)
  {
    pimpl_->addShader(shader);
  }

  void ShaderState::removeShader(Shader const& shader)
  {
    pimpl_->removeShader(shader);
  }

  void ShaderState::setEntryPoint(Shader const& shader, std::string const& name)
  {
    pimpl_->setEntryPoint(shader, name);
  }

  [[nodiscard]] std::string ShaderState::getEntryPoint(Shader const& shader) const
  {
    return pimpl_->getEntryPoint(shader);
  }

}  // namespace vulkan