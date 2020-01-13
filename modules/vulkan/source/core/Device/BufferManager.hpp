#pragma once
#include <utils/allocator.hpp>
#include "../../utils.hpp"

namespace vulkan
{
  // BufferBlock ------------------------------------------------------------------------------------------------------

  class BufferBlock
  {
   public:
    explicit BufferBlock(vk::Device device, utils::allocator::Allocator allocator, utils::SizeT blockSize,
        vk::BufferUsageFlags const& usage, VezMemoryFlags memoryType);

    ~BufferBlock();

    std::pair<vk::Buffer, utils::allocator::Allocation> allocate(utils::SizeT size, utils::AlignmentT alignment);

   private:
    vk::Device device_;
    utils::allocator::Allocator allocator_;
    utils::SizeT blockSize_;
    vk::Buffer vkBuffer_;
  };

  // BufferManager ----------------------------------------------------------------------------------------------------

  class BufferManager
  {
   public:
    explicit BufferManager(vk::Device device, vk::BufferUsageFlags const& usage, VezMemoryFlags memoryType,
        utils::SizeT blockSize, utils::allocator::Allocator allocator);

    BufferManager(BufferManager const& BufferManager) = delete;

    BufferManager(BufferManager&& BufferManager) = default;

    BufferManager& operator=(BufferManager const& BufferManager) = delete;

    BufferManager& operator=(BufferManager&& BufferManager) = default;

    std::pair<vk::Buffer, utils::allocator::Allocation> allocate(utils::SizeT size, utils::AlignmentT alignment)
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

      bufferBlocks_.emplace_back(device_, allocator_, blockSize_, usage_, memoryType_);
      return bufferBlocks_.back().allocate(size, alignment);
    }

   private:
    vk::Device device_;
    vk::BufferUsageFlags usage_;
    VezMemoryFlags memoryType_;
    utils::SizeT blockSize_;
    utils::allocator::Allocator allocator_;
    std::vector<BufferBlock> bufferBlocks_;
  };

}  // namespace vulkan