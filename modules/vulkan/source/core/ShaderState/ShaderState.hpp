#pragma once
#include <map>
#include "../Device/Device.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  struct ShaderInfo
  {
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

    ~ShaderStateImpl();

    [[nodiscard]] VezPipeline getVkPipeline() const
    {
      return vkPipeline_;
    }

    void addShader(Shader const& shader);

    void removeShader(Shader const& shader)
    {
      shaders_.erase(shader);
    }

    void setEntryPoint(Shader const& shader, std::string const& name);

    [[nodiscard]] std::string getEntryPoint(Shader const& shader) const;

    void update();

   private:
    std::shared_ptr<DeviceImpl> device_;
    std::map<Shader, ShaderInfo> shaders_;
    VezPipeline vkPipeline_ = {};
    bool needUpdate_ = true;
  };

}  // namespace vulkan