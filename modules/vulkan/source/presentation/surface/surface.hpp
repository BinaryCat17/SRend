#pragma once
#include <wsystem/vulkan.hpp>
#include "../../core/Device/Device.hpp"

namespace vulkan
{
  class surface_t;
  using surface = std::shared_ptr<surface_t>;

  // utils ----------------------------------------------------------------------------------------

  namespace application_extensions
  {
    class presentation : public base_t
    {
     public:
      presentation(wsystem::Manager const& manager) : manager_(manager)
      {
      }

      static base make(wsystem::Manager const& manager)
      {
        return std::make_shared<presentation>(manager);
      }

      std::vector<char const*> vk_extensions() const override
      {
        return wsystem::getVulkanInstanceExtensions(manager_);
      }

     private:
      wsystem::Manager const& manager_;
    };
  }  // namespace application_extensions

  // surface
  // ----------------------------------------------------------------------------------------------

  surface create_surface(application application, wsystem::Window window);

  vk::SurfaceCapabilitiesKHR get_capabilities(surface surface, physical_device physical_device);

  bool get_support(surface surface, queue queue);
}  // namespace vulkan