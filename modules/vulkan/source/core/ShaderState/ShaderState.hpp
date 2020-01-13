#pragma once
#include <map>
#include "../Device/Device.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  struct ShaderInfo
  {
    Shader shader;
    std::string entryPoint = "main";
    std::map<utils::IndexT, utils::SharedAnyPtr> specConstants = {};
  };

  // ShaderStateImpl --------------------------------------------------------------------------------------------------

  class ShaderStateImpl
  {
   public:
    ShaderStateImpl(std::shared_ptr<DeviceImpl> device, ShaderStateCreateFlags const& createFlags);

    ShaderStateImpl(ShaderStateImpl const&) = delete;

    ShaderStateImpl(ShaderStateImpl&&) = delete;

    ShaderStateImpl& operator=(ShaderStateImpl const&) = delete;

    ShaderStateImpl& operator=(ShaderStateImpl&&) = delete;

    [[nodiscard]] VezPipeline getVkPipeline() const
    {
      return vkPipeline_;
    }

    void addShader(Shader const& shader);

    void setShaderEntryPoint(utils::IndexT index, std::string const& name);

    void setShaderSpecConstant(utils::IndexT index, utils::IndexT constantId, utils::SharedAnyPtr const& pData);

    void removeShader(utils::IndexT index);

    void update();

   private:
    std::shared_ptr<DeviceImpl> device_;
    std::vector<ShaderInfo> shaders_;
    VezPipeline vkPipeline_ = {};
    bool needUpdate_ = true;
  };

}  // namespace vulkan