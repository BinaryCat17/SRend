#pragma once
#include "../Device/DeviceImpl.hpp"
#include "Shader.hpp"

namespace vulkan
{
  // ShaderImpl -------------------------------------------------------------------------------------------------------

  class ShaderImpl
  {
   public:
    ShaderImpl(Device device, ShaderStage stage, std::vector<std::string> const& code, std::string const& entryPoint);

    ~ShaderImpl();

    [[nodiscard]] Device const& getDevice() const
    {
      return device_;
    }

    [[nodiscard]] vk::ShaderModule getVkShaderModule() const
    {
      return vkShaderModule_;
    }

   private:
    Device device_;
    vk::ShaderModule vkShaderModule_;
  };

}  // namespace vulkan