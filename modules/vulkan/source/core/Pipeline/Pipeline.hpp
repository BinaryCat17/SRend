#pragma once
#include "../Shader/Shader.hpp"
#include "../command_buffer/CommandBuffer.hpp"

namespace vulkan
{
  // utils
  // -------------------------------------------------------------------------------------------------

  class spec_const
  {
   public:
    spec_const(utils::SharedAnyPtr ptr, uint32_t id) : ptr_(ptr), id_(id)
    {
    }

    uint32_t id() const
    {
      return id_;
    }

    size_t size() const
    {
      return ptr_.size();
    }

    void const* data() const
    {
      return ptr_.data();
    }

   private:
    utils::SharedAnyPtr ptr_;
    uint32_t id_;
  };

  struct shader_module_info
  {
    shader shader_;
    std::string entry_point_;
    std::vector<spec_const> infos_;
  };

  // pipeline
  // ----------------------------------------------------------------------------------------------

  class pipeline_t;
  using pipeline = std::shared_ptr<pipeline_t>;

  pipeline create_pipeline(device device, std::vector<shader_module_info> const& shader_modules);

  void cmd_bind(command_buffer command_buffer, pipeline pipeline);
}  // namespace vulkan