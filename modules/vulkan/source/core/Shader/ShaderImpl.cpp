#include "ShaderImpl.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  vk::ShaderStageFlagBits toVkShaderStage(ShaderStage stage)
  {
    switch (stage)
    {
      case ShaderStage::Vertex:
        return vk::ShaderStageFlagBits::eVertex;
      case ShaderStage::Fragment:
        return vk::ShaderStageFlagBits::eFragment;
    }
  }

  vk::ShaderModule createVkShaderModule(
      Device const& device, ShaderStage stage, std::vector<std::string> const& code, std::string const& entryPoint)
  {
    std::string strCode = utils::strVecToStr(code);

    VezShaderModuleCreateInfo moduleCreateInfo = {};
    moduleCreateInfo.stage = static_cast<VkShaderStageFlagBits>(toVkShaderStage(stage));
    moduleCreateInfo.pCode = reinterpret_cast<uint32_t const*>(strCode.data());
    moduleCreateInfo.codeSize = strCode.size();
    moduleCreateInfo.pEntryPoint = entryPoint.data();

    VkShaderModule result = nullptr;
    checkResult(vezCreateShaderModule(
        device.getImpl()->getVkDevice(), &moduleCreateInfo, reinterpret_cast<VkShaderModule*>(&result)));
    return result;
  }

  // ShaderImpl -------------------------------------------------------------------------------------------------------

  ShaderImpl::ShaderImpl(
      Device device, ShaderStage stage, std::vector<std::string> const& code, std::string const& entryPoint)
      : device_(std::move(device)), vkShaderModule_(createVkShaderModule(device, stage, code, entryPoint))
  {
  }

  ShaderImpl::~ShaderImpl()
  {
    vezDestroyShaderModule(device_.getImpl()->getVkDevice(), vkShaderModule_);
  }

}  // namespace vulkan