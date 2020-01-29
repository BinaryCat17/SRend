#include "BufferManager.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  vk::Buffer createVkVBuffer(
      vk::Device device, utils::SizeT size, vk::BufferUsageFlags const& usage, VezMemoryFlags memoryType)
  {
    VezBufferCreateInfo createInfo = {};
    createInfo.size = size;
    createInfo.usage = static_cast<VkBufferUsageFlags>(usage);

    VkBuffer result = nullptr;
    checkResult(vezCreateBuffer(device, memoryType, &createInfo, &result));
    return result;
  }

  // BufferBlock ------------------------------------------------------------------------------------------------------

  BufferBlock::BufferBlock(vk::Device device, utils::allocator::Allocator allocator, utils::SizeT blockSize,
      vk::BufferUsageFlags const& usage, VezMemoryFlags memoryType)
      : device_(device),
        allocator_(std::move(allocator)),
        blockSize_(blockSize),
        vkBuffer_(createVkVBuffer(device, blockSize, usage, memoryType))
  {
  }

  BufferBlock::~BufferBlock()
  {
    vezDestroyBuffer(device_, vkBuffer_);
  }

  std::pair<vk::Buffer, utils::allocator::Allocation> BufferBlock::allocate(
      utils::SizeT size, utils::AlignmentT alignment)
  {
    if (allocator_.requiredExtension(size, alignment) + allocator_.size() > blockSize_)
    {
      throw std::runtime_error("no place for allocation");
    }
    return std::make_pair(vkBuffer_, allocator_.allocate(size, alignment));
  }

  // BufferManager ----------------------------------------------------------------------------------------------------

  BufferManager::BufferManager(vk::Device device, vk::BufferUsageFlags const& usage, VezMemoryFlags memoryType,
      utils::SizeT blockSize)
      : device_(device), usage_(usage), memoryType_(memoryType), blockSize_(blockSize)
  {
  }

  std::pair<vk::Buffer, utils::allocator::Allocation> BufferManager::allocate(
      utils::SizeT size, utils::AlignmentT alignment)
  {
    for (auto& block : bufferBlocks_)
    {
      try
      {
        return block.allocate(size, alignment);
      }
      catch (std::runtime_error const&)
      {
      }
    }

    bufferBlocks_.emplace_back(device_, utils::allocator::Allocator(), blockSize_, usage_, memoryType_);
    return bufferBlocks_.back().allocate(size, alignment);
  }

}  // namespace vulkan
