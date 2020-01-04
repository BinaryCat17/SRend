#include <regex>
#include "ShaderImpl.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  ShaderStage pickStageFromStr(std::string const& fileFormat)
  {
    if (fileFormat == "vert")
    {
      return ShaderStage::Vertex;
    }
    if (fileFormat == "frag")
    {
      return ShaderStage::Fragment;
    }
    throw std::runtime_error("invalid Shader file format");
  }

  ShaderStage pickShaderStage(std::filesystem::path const& path)
  {
    std::regex regex("([[:alpha:]]+)(.)(vert|frag)");
    std::string filename = path.filename().string();
    std::smatch result;

    if (std::regex_search(filename, result, regex))
    {
      return pickStageFromStr(result[3].str());
    }
    throw std::runtime_error("specified defective path to Shader");
  }

  // Shader -----------------------------------------------------------------------------------------------------------

  Shader::Shader(
      Device const& device, ShaderStage stage, std::vector<std::string> const& code, std::string const& entryPoint)
      : pimpl_(std::make_shared<ShaderImpl>(device, stage, code, entryPoint))
  {
  }

  Shader::Shader(Device const& device, std::filesystem::path const& path, std::string const& entryPoint)
      : Shader(device, pickShaderStage(path), utils::readFileToStringVec(path), entryPoint)
  {
  }

}  // namespace vulkan