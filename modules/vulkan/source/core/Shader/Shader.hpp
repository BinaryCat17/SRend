#pragma once
#include "../Device/Device.hpp"
#include "Shader.hpp"

namespace vulkan
{
  // ShaderImpl -------------------------------------------------------------------------------------------------------

  class ShaderImpl
  {
   public:
    ShaderImpl(std::shared_ptr<DeviceImpl> device, ShaderCreateFlags createFlags);

    ShaderImpl(ShaderImpl const&) = delete;

    ShaderImpl(ShaderImpl&&) = delete;

    ShaderImpl& operator=(ShaderImpl const&) = delete;

    ShaderImpl& operator=(ShaderImpl&&) = delete;

    ~ShaderImpl();

    [[nodiscard]] std::shared_ptr<DeviceImpl> const& getDevice() const
    {
      return device_;
    }

    [[nodiscard]] vk::ShaderModule getVkShaderModule() const
    {
      return vkShaderModule_;
    }

    void load(std::filesystem::path const& path);

    void load(ShaderType type, std::vector<std::string> const& code);

   private:
    std::shared_ptr<DeviceImpl> device_;
    vk::ShaderModule vkShaderModule_;
  };

}  // namespace vulkan