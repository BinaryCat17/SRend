#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  enum class ShaderStage
  {
    Vertex,
    Fragment,
  };

  // Shader -----------------------------------------------------------------------------------------------------------

  class ShaderImpl;

  class Shader
  {
   public:
    Shader(Device const& device, ShaderStage stage, std::vector<std::string> const& code,
        std::string const& entryPoint = "main");

    Shader(Device const& device, std::filesystem::path const& path, std::string const& entryPoint = "main");

   private:
    std::shared_ptr<ShaderImpl> pimpl_;
  };

}  // namespace vulkan