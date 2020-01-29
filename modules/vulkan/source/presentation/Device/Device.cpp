#include "Device.hpp"
#include "../RenderWindow/RenderWindow.hpp"

namespace vulkan::presentation
{
  // Device -----------------------------------------------------------------------------------------------------------

  RenderWindow createRenderWindow(Device const& device, RenderWindowCreateFlags const& createFlags,
      wsystem::Window const& window, Format format, ColorSpace colorSpace)
  {
    return RenderWindow(std::make_shared<RenderWindowImpl>(device.getImpl(), createFlags, window, format, colorSpace));
  }

}  // namespace vulkan::presentation