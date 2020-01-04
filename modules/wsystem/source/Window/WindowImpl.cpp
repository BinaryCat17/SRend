#include "WindowImpl.hpp"
#include "../Manager/BaseManager.hpp"

namespace wsystem
{
  // WindowImpl -------------------------------------------------------------------------------------------------------

  wsystem::WindowImpl::~WindowImpl()
  {
    pmanager_->removeWindow(pbase_);
  }

  void WindowImpl::update()
  {
    if (pbase_->isShouldClose())
    {
      onShouldClose();
    }
    if (pbase_->isResized())
    {
      onResize();
    }
    if (pbase_->isMoved())
    {
      onMove();
    }
  }

}  // namespace wsystem
