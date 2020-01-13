#pragma once
#include "../../../include/vulkan/core.hpp"
#include "../../utils.hpp"

namespace vulkan
{
  // ApplicationImpl --------------------------------------------------------------------------------------------------

  class ApplicationImpl
  {
   public:
    explicit ApplicationImpl(ApplicationCreateFlags const& createFlags, ApplicationInfo const& appInfo,
        ExtensionsFlags const& extensions, ValidationLayersFlags const& layers, utils::debug::Messenger messenger);

    ApplicationImpl(ApplicationImpl const&) = delete;

    ApplicationImpl(ApplicationImpl&&) = delete;

    ApplicationImpl& operator=(ApplicationImpl const&) = delete;

    ApplicationImpl& operator=(ApplicationImpl&&) = delete;

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

    // interface

    [[nodiscard]] std::vector<PhysicalDevice> const& getSupportedPhysicalDevices() const
    {
      return physicalDevices_;
    }

   private:
    ExtensionsFlags enabledExtensions_;
    vk::Instance vkInstance_;
    vk::DispatchLoaderDynamic vkDllLoader_;
    utils::debug::Messenger messenger_;
    vk::DebugUtilsMessengerEXT vkDebugMessenger_;
    std::vector<PhysicalDevice> physicalDevices_;
  };

}  // namespace vulkan