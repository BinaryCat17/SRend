#pragma once
#include <utils/debug.hpp>
#include "../PhysicalDevice/PhysicalDevice.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(ApplicationCreate, {};)

  SR_MAKE_BIT_FLAGS(Extensions, {
    Presentation = 1u << 0u
  };)

  SR_MAKE_BIT_FLAGS(ValidationLayers, {
    StandardValidation = 1u << 0u
  };)

  // clang-format on

  ExtensionsFlags getSupportedExtensions();

  ValidationLayersFlags getSupportedValidationLayers();

  struct ApplicationInfo
  {
    ApplicationInfo() = default;

    ApplicationInfo(std::string appName, std::unique_ptr<utils::Version> appVersion, std::string engineName,
        std::unique_ptr<utils::Version> engineVersion)
        : appName(std::move(appName)),
          appVersion(std::move(appVersion)),
          engineName(std::move(engineName)),
          engineVersion(std::move(engineVersion))
    {
    }

    std::string appName = "Unknown";
    std::unique_ptr<utils::Version> appVersion = std::make_unique<utils::VersionList>(utils::VersionList{0, 0, 0});
    std::string engineName = "Unknown";
    std::unique_ptr<utils::Version> engineVersion = std::make_unique<utils::VersionList>(utils::VersionList{0, 0, 0});
    ;
  };

  // Application ------------------------------------------------------------------------------------------------------

  class ApplicationImpl;

  class Application
  {
   public:
    explicit Application(std::shared_ptr<ApplicationImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<ApplicationImpl> const& getImpl() const
    {
      return pimpl_;
    }

    explicit Application(ApplicationCreateFlags const& createFlags, ApplicationInfo const& appInfo,
        ExtensionsFlags const& extensions = {}, ValidationLayersFlags const& layers = {},
        utils::debug::Messenger const& messenger = {});

    [[nodiscard]] std::vector<PhysicalDevice> getSupportedPhysicalDevices() const;

   private:
    std::shared_ptr<ApplicationImpl> pimpl_;
  };

}  // namespace vulkan