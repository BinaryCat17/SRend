#pragma once
#include "../../utils.hpp"
#include "../PhysicalDevice/PhysicalDeviceImpl.hpp"
#include "Application.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  using VkDebugMessenger = vk::UniqueHandle<vk::DebugUtilsMessengerEXT, vk::DispatchLoaderDynamic>;

  // ApplicationImpl --------------------------------------------------------------------------------------------------

  class ApplicationImpl
  {
   public:
    explicit ApplicationImpl(ApplicationCreateFlags const& createFlags, ApplicationInfo const& appInfo,
        ExtensionsFlags const& extensions, ValidationLayersFlags const& layers, utils::debug::Messenger messenger);

    ~ApplicationImpl();

    [[nodiscard]] ExtensionsFlags const& getEnabledExtensions() const
    {
      return enabledExtensions_;
    }

    [[nodiscard]] vk::Instance getVkInstance() const
    {
      return vkInstance_;
    }

    [[nodiscard]] vk::DispatchLoaderDynamic const& getVkDllLoader() const
    {
      return vkDllLoader_;
    }

    [[nodiscard]] std::vector<PhysicalDevice> const& getSupportedPhysicalDevices() const
    {
      return physicalDevices_;
    }

   private:
    ExtensionsFlags enabledExtensions_;
    vk::Instance vkInstance_;
    vk::DispatchLoaderDynamic vkDllLoader_;
    utils::debug::Messenger messenger_;
    VkDebugMessenger vkDebugMessenger_;
    std::vector<PhysicalDevice> physicalDevices_;
  };

}  // namespace vulkan