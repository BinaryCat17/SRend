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
      std::shared_ptr<DeviceImpl> const& device, ShaderType type, std::vector<std::string> const& code)
  {
    std::string strCode = utils::strVecToStr(code);

    VezShaderModuleCreateInfo moduleCreateInfo = {};
    moduleCreateInfo.stage = static_cast<VkShaderStageFlagBits>(toVkShaderStage(type));
    moduleCreateInfo.pCode = reinterpret_cast<uint32_t const*>(strCode.data());
    moduleCreateInfo.codeSize = strCode.size();
    moduleCreateInfo.pEntryPoint = "main";

    VkShaderModule result = nullptr;
    checkResult(
        vezCreateShaderModule(device->getVkDevice(), &moduleCreateInfo, reinterpret_cast<VkShaderModule*>(&result)));
    return result;
  }

  ShaderType pickTypeFromStr(std::string const& fileFormat)
  {
    if (fileFormat == "vert")
    {
      return ShaderType::Vertex;
    }
    if (fileFormat == "frag")
    {
      return ShaderType::Fragment;
    }
    throw std::runtime_error("invalid Shader file format");
  }

  ShaderType pickShaderType(std::filesystem::path const& path)
  {
    std::regex regex("([[:alpha:]]+)(.)(vert|frag)");
    std::string filename = path.filename().string();
    std::smatch result;

    if (std::regex_search(filename, result, regex))
    {
      return pickTypeFromStr(result[3].str());
    }
    throw std::runtime_error("specified defective path to Shader");
  }

  // ShaderImpl -------------------------------------------------------------------------------------------------------

  ShaderImpl::ShaderImpl(std::shared_ptr<DeviceImpl> device, ShaderCreateFlags) : device_(std::move(device))
  {
  }

  ShaderImpl::~ShaderImpl()
  {
    vezDestroyShaderModule(device_->getVkDevice(), vkShaderModule_);
  }

  void ShaderImpl::load(std::filesystem::path const& path)
  {
    vkShaderModule_ = createVkShaderModule(device_, pickShaderType(path), utils::readFileToStringVec(path));
  }

  void ShaderImpl::load(ShaderType type, std::vector<std::string> const& code)
  {
    vkShaderModule_ = createVkShaderModule(device_, type, code);
  }

  // Shader -----------------------------------------------------------------------------------------------------------

  void Shader::load(std::filesystem::path const& path)
  {
    pimpl_->load(path);
  }

  void Shader::load(ShaderType type, std::vector<std::string> const& code)
  {
    pimpl_->load(type, code);
  }

}  // namespace vulkan