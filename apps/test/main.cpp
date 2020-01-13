#include <iostream>
#include <vulkan/core.hpp>

int main()
{
  try
  {
    vulkan::Application application(
        {}, {}, vulkan::ExtensionsFlagBits::Presentation, vulkan::ValidationLayersFlagBits::StandardValidation);

    auto physicalDevices = application.getSupportedPhysicalDevices();

    std::cout << "Supported physical devices : " << std::endl;

    for (auto const& physicalDevice : physicalDevices)
    {
      using namespace magic_enum::ostream_operators;

      std::cout << "\tPhysical device : " << physicalDevice.name() << ". Type : " << physicalDevice.type() << std::endl;
    }

    if (!physicalDevices.empty())
    {
      std::cout << "Selected physical device : " << physicalDevices[0].name() << std::endl;
    }
    else
    {
      throw std::runtime_error("no physical device supports vulkan");
    }
  }
  catch (std::exception const& ex)
  {
    std::cerr << ex.what() << std::endl;
  }
}