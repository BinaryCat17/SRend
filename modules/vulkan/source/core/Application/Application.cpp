#include "ApplicationImpl.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  ExtensionsFlags getSupportedExtensions()
  {
    ExtensionsFlags result;
    auto extensions = vk::enumerateInstanceExtensionProperties();

    for (auto const& ex : extensions)
    {
      std::string strEx = ex.extensionName;

      if (strEx.find("Surface") != strEx.size())
      {
        result |= ExtensionsFlagBits::Presentation;
      }
    }

    return result;
  }

  ValidationLayersFlags getSupportedValidationLayers()
  {
    ValidationLayersFlags result;
    auto layers = vk::enumerateInstanceLayerProperties();

    for (auto const& layer : layers)
    {
      std::string strLayer = layer.layerName;
      if (strLayer == "VK_LAYER_KHRONOS_validation")
      {
        result |= ValidationLayersFlagBits::StandardValidation;
      }
    }

    return result;
  }

  // Application ------------------------------------------------------------------------------------------------------

  Application::Application(ApplicationCreateFlags const& createFlags, ApplicationInfo const& appInfo,
      ExtensionsFlags const& extensions, ValidationLayersFlags const& layers, utils::debug::Messenger const& messenger)
      : pimpl_(std::make_shared<ApplicationImpl>(createFlags, appInfo, extensions, layers, messenger))
  {
  }

  std::vector<PhysicalDevice> Application::getSupportedPhysicalDevices() const
  {
    return pimpl_->getSupportedPhysicalDevices();
  }

}  // namespace vulkan
