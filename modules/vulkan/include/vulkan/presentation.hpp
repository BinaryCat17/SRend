#pragma once
#include <wsystem/vulkan.hpp>
#include "core.hpp"

namespace vulkan::presentation
{
  // Enums ------------------------------------------------------------------------------------------------------------

  enum class ColorSpace
  {
    SrgbNonlinear = 0,
  };

  // RenderWindow -----------------------------------------------------------------------------------------------------

  // clang-format off

    SR_MAKE_BIT_FLAGS(RenderWindowCreate, {};)

  // clang-format on

  class RenderWindowImpl;

  class RenderWindow
  {
   public:
    explicit RenderWindow(std::shared_ptr<RenderWindowImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<RenderWindowImpl> const& getImpl() const
    {
      return pimpl_;
    }

    [[nodiscard]] Semaphore present(Image const& image, std::vector<WaitInfo> const& waitInfo);

   private:
    std::shared_ptr<RenderWindowImpl> pimpl_;
  };

  // Device -----------------------------------------------------------------------------------------------------------

  RenderWindow createRenderWindow(Device const& device, RenderWindowCreateFlags const& createFlags,
      wsystem::Window const& window, Format format, ColorSpace colorSpace);

}  // namespace vulkan::presentation