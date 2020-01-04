#include "ApplicationImpl.hpp"
#include <wsystem/vulkan.hpp>

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  std::vector<char const*> getVkApplicationExtensions(ExtensionsFlags const& extensions)
  {
    std::vector<char const*> result;

    if (extensions & ExtensionsFlagBits::Presentation)
    {
      auto vkExtensions = wsystem::getVulkanInstanceExtensions(wsystem::Manager{});
      std::copy(vkExtensions.cbegin(), vkExtensions.cend(), std::back_inserter(result));
    }

    return result;
  }

  std::vector<char const*> toVkApplicationValidationLayers(ValidationLayersFlags const& layers)
  {
    std::vector<char const*> result;

    if (layers & ValidationLayersFlagBits::StandardValidation)
    {
      result.push_back("VK_LAYER_KHRONOS_validation");
    }

    return result;
  }

  vk::Instance createVkInstance(
      ApplicationInfo const& appInfo, ExtensionsFlags const& extensions, ValidationLayersFlags const& layers)
  {
    auto vkExtensions = getVkApplicationExtensions(extensions);
    auto vkLayers = toVkApplicationValidationLayers(layers);
    if (!vkLayers.empty())
    {
      vkExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    VezApplicationInfo vkAppApplicationInfo = {};
    vkAppApplicationInfo.pApplicationName = appInfo.appName.data();
    vkAppApplicationInfo.applicationVersion = appInfo.appVersion->toUint();
    vkAppApplicationInfo.pEngineName = appInfo.engineName.data();
    vkAppApplicationInfo.engineVersion = appInfo.engineVersion->toUint();

    VezInstanceCreateInfo createInfo = {};
    createInfo.pApplicationInfo = &vkAppApplicationInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(vkExtensions.size());
    createInfo.ppEnabledExtensionNames = vkExtensions.data();
    createInfo.enabledLayerCount = static_cast<uint32_t>(vkLayers.size());
    createInfo.ppEnabledLayerNames = vkLayers.data();

    VkInstance instance = nullptr;
    checkResult(vezCreateInstance(&createInfo, &instance));
    return instance;
  }

  vk::DebugUtilsMessageSeverityFlagsEXT toVkMessageSeverity(utils::debug::MessageSeverityFlags const& severity)
  {
    vk::DebugUtilsMessageSeverityFlagsEXT result = {};

    if (severity & utils::debug::MessageSeverityFlagBits::error)
    {
      result |= vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
    }
    if (severity & utils::debug::MessageSeverityFlagBits::warning)
    {
      result |= vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning;
    }
    if (severity & utils::debug::MessageSeverityFlagBits::info)
    {
      result |= vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo;
    }
    if (severity & utils::debug::MessageSeverityFlagBits::notice)
    {
      result |= vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose;
    }

    return result;
  }

  vk::DebugUtilsMessageTypeFlagsEXT toVkMessageType(utils::debug::MessageTypeFlags const& type)
  {
    vk::DebugUtilsMessageTypeFlagsEXT result = {};

    if (type & utils::debug::MessageTypeFlagBits::general)
    {
      result |= vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral;
    }
    if (type & utils::debug::MessageTypeFlagBits::performance)
    {
      result |= vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;
    }
    if (type & utils::debug::MessageTypeFlagBits::validation)
    {
      result |= vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation;
    }

    return result;
  }

  utils::debug::MessageSeverityFlagBits toMessageSeverity(vk::DebugUtilsMessageSeverityFlagBitsEXT severity)
  {
    switch (severity)
    {
      case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
        return utils::debug::MessageSeverityFlagBits::error;

      case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
        return utils::debug::MessageSeverityFlagBits::warning;

      case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:
        return utils::debug::MessageSeverityFlagBits::info;

      case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:
        return utils::debug::MessageSeverityFlagBits::notice;

      default:
        throw std::runtime_error("undefined message severity");
    }
  }

  utils::debug::MessageTypeFlags toMessageTypeFlags(vk::DebugUtilsMessageTypeFlagsEXT const& type)
  {
    utils::debug::MessageTypeFlags result;

    if (type & vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral)
    {
      result |= utils::debug::MessageTypeFlagBits::general;
    }
    if (type & vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance)
    {
      result |= utils::debug::MessageTypeFlagBits::performance;
    }
    if (type & vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation)
    {
      result |= utils::debug::MessageTypeFlagBits::validation;
    }

    return result;
  }

  VKAPI_ATTR VkBool32 VKAPI_CALL vulkanCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
      VkDebugUtilsMessageTypeFlagsEXT messageType, VkDebugUtilsMessengerCallbackDataEXT const* pCallbackData,
      void* messenger)
  {
    reinterpret_cast<utils::debug::Messenger const*>(messenger)->report(
        std::string("Vulkan callback : ") + pCallbackData->pMessage,
        toMessageSeverity(static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>(messageSeverity)),
        toMessageTypeFlags(static_cast<vk::DebugUtilsMessageTypeFlagsEXT>(messageType)));

    return VK_FALSE;
  }

  VkDebugMessenger createVkDebugMessenger(vk::Instance instance, ValidationLayersFlags const& layers,
      utils::debug::Messenger const& messenger, vk::DispatchLoaderDynamic const& vkDllLoader)
  {
    if (!toVkApplicationValidationLayers(layers).empty())
    {
      vk::DebugUtilsMessengerCreateInfoEXT createInfo = {};
      createInfo.messageSeverity = toVkMessageSeverity(messenger.severityFilter());
      createInfo.messageType = toVkMessageType(messenger.typeFilter());
      createInfo.pfnUserCallback = vulkanCallback;
      createInfo.pUserData = const_cast<utils::debug::Messenger*>(&messenger);
      return instance.createDebugUtilsMessengerEXTUnique(createInfo, nullptr, vkDllLoader);
    }
    else
    {
      return vk::UniqueHandle<vk::DebugUtilsMessengerEXT, vk::DispatchLoaderDynamic>{};
    }
  }

  std::vector<PhysicalDevice> getSupportedPhysicalDevices(vk::Instance vkInstance)
  {
    std::vector<PhysicalDevice> result;

    for (vk::PhysicalDevice vkPhysicalDevice : vkInstance.enumeratePhysicalDevices())
    {
      result.emplace_back(std::make_shared<PhysicalDeviceImpl>(vkPhysicalDevice));
    }

    return result;
  }

  // ApplicationImpl --------------------------------------------------------------------------------------------------

  ApplicationImpl::ApplicationImpl(ApplicationCreateFlags const&, ApplicationInfo const& appInfo,
      ExtensionsFlags const& extensions, ValidationLayersFlags const& layers, utils::debug::Messenger messenger)
      : enabledExtensions_(extensions),
        vkInstance_(createVkInstance(appInfo, extensions, layers)),
        vkDllLoader_(vkInstance_),
        messenger_(std::move(messenger)),
        vkDebugMessenger_(createVkDebugMessenger(vkInstance_, layers, messenger_, vkDllLoader_))
  {
  }

  ApplicationImpl::~ApplicationImpl()
  {
    vezDestroyInstance(vkInstance_);
  }

}  // namespace vulkan