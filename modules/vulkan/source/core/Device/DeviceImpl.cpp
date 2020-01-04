#include "DeviceImpl.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  std::vector<char const*> getVkDeviceExtensions(ExtensionsFlags const& extensions)
  {
    std::vector<char const*> result;

    if (extensions & ExtensionsFlagBits::Presentation)
    {
      result.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    }

    return result;
  }

  vk::Device createVkDevice(const PhysicalDevice& physicalDevice, ExtensionsFlags const& extensions)
  {
    auto vkExtensions = getVkDeviceExtensions(extensions);

    VezDeviceCreateInfo createInfo = {};
    createInfo.enabledExtensionCount = static_cast<uint32_t>(vkExtensions.size());
    createInfo.ppEnabledExtensionNames = vkExtensions.data();

    VkDevice vkDevice = nullptr;
    checkResult(vezCreateDevice(physicalDevice.getImpl()->getVkPhysicalDevice(), &createInfo, &vkDevice));
    return vkDevice;
  }

  DeviceQueues createQueues(vk::Device device)
  {
    DeviceQueues result;

    vezGetDeviceGraphicsQueue(device, 0, reinterpret_cast<VkQueue*>(&result.graphicQueue));
    vezGetDeviceComputeQueue(device, 0, reinterpret_cast<VkQueue*>(&result.computeQueue));
    vezGetDeviceTransferQueue(device, 0, reinterpret_cast<VkQueue*>(&result.transferQueue));

    return result;
  }

  DeviceBuffers createBuffers(vk::Device device)
  {
    vk::BufferUsageFlags allSupportedUsage =
        vk::BufferUsageFlagBits::eUniformBuffer | vk::BufferUsageFlagBits::eIndexBuffer |
        vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferSrc |
        vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eStorageBuffer |
        vk::BufferUsageFlagBits::eStorageTexelBuffer | vk::BufferUsageFlagBits::eUniformTexelBuffer;
    vk::BufferUsageFlags stagingUsage = vk::BufferUsageFlagBits::eTransferSrc | vk::BufferUsageFlagBits::eTransferDst;

    BufferManager deviceLocalManager(device, allSupportedUsage, VEZ_MEMORY_GPU_ONLY, 300 * 1000 * 1000, {});
    BufferManager hostLocalManager(device, allSupportedUsage, VEZ_MEMORY_CPU_ONLY, 300 * 1000 * 1000, {});
    BufferManager deviceVisibleManager(device, allSupportedUsage, VEZ_MEMORY_CPU_TO_GPU, 300 * 1000 * 1000, {});
    BufferManager stagingManager(device, stagingUsage, VEZ_MEMORY_CPU_ONLY, 300 * 1000 * 1000, {});

    return DeviceBuffers{deviceLocalManager, hostLocalManager, deviceVisibleManager, stagingManager};
  }

  // DeviceImpl -------------------------------------------------------------------------------------------------------

  DeviceImpl::DeviceImpl(Application const& application, DeviceCreateFlags const&, PhysicalDevice const& physicalDevice)
      : application_(application),
        vkDevice_(createVkDevice(physicalDevice, application.getImpl()->getEnabledExtensions())),
        queues_(createQueues(vkDevice_)),
        buffers_(createBuffers(vkDevice_))
  {
  }

  DeviceImpl::~DeviceImpl()
  {
    vezDestroyDevice(vkDevice_);
  }

}  // namespace vulkan
