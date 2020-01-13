#pragma once
#include "../../core/Application/Application.hpp"
#include "surface.hpp"

namespace vulkan
{
  // surface_t
  // --------------------------------------------------------------------------------------------

  class surface_t
  {
   public:
    surface_t(application application, wsystem::Window window)
        : application_(application), vk_surface_(wsystem::createVulkanSurface(window, application_->get_vk_instance()))
    {
    }

    ~surface_t()
    {
      application_->get_vk_instance().destroySurfaceKHR(vk_surface_);
    }

    application get_application() const
    {
      return application_;
    }

    vk::SurfaceKHR get_vk_surface() const
    {
      return vk_surface_;
    }

   private:
    application application_;
    vk::SurfaceKHR vk_surface_;
  };
}  // namespace vulkan