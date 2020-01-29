#include "Presenter.hpp"
#include "../../../include/render/core.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  // PresenterImpl ----------------------------------------------------------------------------------------------------

  PresenterImpl::PresenterImpl(vulkan::Device const& device, utils::Extent2D const& extent)
      : device_(device),
        attachment_(device, {}, utils::Extent3D(extent), vulkan::Format::B8G8R8A8Unorm,
            vulkan::ImageUsageFlagBits::ColorAttachment),
        render_(device, {}, attachment_),
        window_(manager_.createWindow(
            "Render Engine", extent, wsystem::WindowOptionsFlagBits::resizable, wsystem::WindowCreateFlagBits::vulkan)),
        vulkanWindow_(createRenderWindow(
            device, {}, window_, vulkan::Format::B8G8R8A8Unorm, vulkan::presentation::ColorSpace::SrgbNonlinear))
  {
    render_.record(commands_);
    render_.recordPostCommand(postCommands_);
  }

  void PresenterImpl::runLoop()
  {
    bool shouldClose = false;
    window_.onShouldClose().connect([&shouldClose] { shouldClose = true; });
    window_.onResize().connect([this] {
      attachment_ = vulkan::Image(device_, {}, utils::Extent3D(window_.getSize()), vulkan::Format::B8G8R8A8Unorm,
          vulkan::ImageUsageFlagBits::ColorAttachment);
      render_ = Render(device_, {}, attachment_);

      render_.record(commands_);
      render_.recordPostCommand(postCommands_);
    });




    auto renderWaitSemaphore = render_.render({});

    while (!shouldClose)
    {
      manager_.update();
      vulkan::Semaphore presentWaitSemaphore =
          vulkanWindow_.present(attachment_, {{renderWaitSemaphore, vulkan::WaitStageFlagBits::ColorAttachmentOutput}});
      renderWaitSemaphore = render_.render({{presentWaitSemaphore, vulkan::WaitStageFlagBits::Transfer}});
    }
  }

  // Presenter --------------------------------------------------------------------------------------------------------

  Presenter::Presenter(
      vulkan::Device const& device, utils::Extent2D const& extent) : pimpl_(std::make_shared<PresenterImpl>(device, extent))
  {

  }

  Command Presenter::record(std::function<void(vulkan::CommandBuffer&)> const& obj)
  {
   return pimpl_->record(obj);
  }

  void Presenter::erase(Command const& command)
  {
    pimpl_->erase(command);
  }

  void Presenter::runLoop()
  {
    pimpl_->runLoop();
  }

  wsystem::Window Presenter::getWindow() const
  {
    return pimpl_->getWindow();
  }

  Command Presenter::recordPostCommand(std::function<void(vulkan::CommandBuffer&)> const& obj)
  {
    return pimpl_->recordPostCommand(obj);
  }

  void Presenter::erasePostCommand(Command const& command)
  {
    pimpl_->erasePostCommand(command);
  }

}  // namespace render