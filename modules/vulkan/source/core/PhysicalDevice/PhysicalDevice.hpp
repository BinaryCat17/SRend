#pragma once
#include <utils/utils.hpp>

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  enum class PhysicalDeviceType
  {
    Other,
    IntegratedGpu,
    DiscreteGpu,
    VirtualGpu,
    Cpu,
  };

  // PhysicalDevice ---------------------------------------------------------------------------------------------------

  class PhysicalDeviceImpl;

  class PhysicalDevice
  {
   public:
    explicit PhysicalDevice(std::shared_ptr<PhysicalDeviceImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<PhysicalDeviceImpl> const& getImpl() const
    {
      return pimpl_;
    }

    [[nodiscard]] std::string name() const;

    [[nodiscard]] PhysicalDeviceType type() const;

   private:
    std::shared_ptr<PhysicalDeviceImpl> pimpl_;
  };

}  // namespace vulkan
