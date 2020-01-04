#pragma once
#include "../Device/DeviceImpl.hpp"
#include "Pipeline.hpp"

namespace vulkan
{
  // pipeline_t --------------------------------------------------------------------------------------------

  class pipeline_t
  {
   public:
    pipeline_t(device device, std::vector<shader_module_info> const& modules);

    ~pipeline_t()
    {
      vezDestroyPipeline(device_->get_vk_device(), vk_pipeline_);
    }

    device get_device() const
    {
      return device_;
    }

    VezPipeline get_vk_pipeline() const
    {
      return vk_pipeline_;
    }

   private:
    device device_;
    VezPipeline vk_pipeline_;
  };
}  // namespace vulkan