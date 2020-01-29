#include "Shader.hpp"
#include <regex>

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  vk::ShaderStageFlagBits toVkShaderStage(ShaderType type)
  {
    return static_cast<vk::ShaderStageFlagBits>(type);
  }

  vk::ShaderModule createVkShaderModule(
      std::shared_ptr<DeviceImpl> const& device, ShaderType type, std::vector<char> const& code)
  {
    VezShaderModuleCreateInfo moduleCreateInfo = {};
    moduleCreateInfo.stage = static_cast<VkShaderStageFlagBits>(toVkShaderStage(type));
    moduleCreateInfo.pCode = reinterpret_cast<uint32_t const*>(code.data());
    moduleCreateInfo.codeSize = code.size() * sizeof(char);
    moduleCreateInfo.pEntryPoint = "main";

    VkShaderModule result = nullptr;
    checkResult(
        vezCreateShaderModule(device->getVkDevice(), &moduleCreateInfo, reinterpret_cast<VkShaderModule*>(&result)));
    return result;
  }

  // ShaderImpl -------------------------------------------------------------------------------------------------------

  ShaderImpl::ShaderImpl(std::shared_ptr<DeviceImpl> device, ShaderCreateFlags) : device_(std::move(device))
  {
  }

  ShaderImpl::~ShaderImpl()
  {
    vezDestroyShaderModule(device_->getVkDevice(), vkShaderModule_);
  }

  void ShaderImpl::load(ShaderType type, std::filesystem::path const& path)
  {
    vkShaderModule_ = createVkShaderModule(device_, type, utils::readBinaryFile(path));
  }

  void ShaderImpl::load(ShaderType type, std::vector<std::string> const& code)
  {
    std::string strCode = utils::stringVecToString(code);
    vkShaderModule_ = createVkShaderModule(device_, type, std::vector<char>(strCode.cbegin(), strCode.cend()));
  }

  // Shader -----------------------------------------------------------------------------------------------------------

  Shader::Shader(Device const& device, ShaderCreateFlags const& createFlags)
      : pimpl_(std::make_shared<ShaderImpl>(device.getImpl(), createFlags))
  {
  }

  void Shader::load(ShaderType type, std::filesystem::path const& path)
  {
    pimpl_->load(type, path);
  }

  void Shader::load(ShaderType type, std::vector<std::string> const& code)
  {
    pimpl_->load(type, code);
  }

}  // namespace vulkan