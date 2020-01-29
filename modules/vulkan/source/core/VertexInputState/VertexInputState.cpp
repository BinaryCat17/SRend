#include "VertexInputState.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  vk::VertexInputRate toVkVertexInputRate(VertexInputRate rate)
  {
    return static_cast<vk::VertexInputRate>(rate);
  }

  utils::SizeT formatSize(Format format)
  {
    switch (format)
    {
      case Format::R32Sfloat:
        return sizeof(float) * 1;

      case Format::R32G32Sfloat:
        return sizeof(float) * 2;

      case Format::R32G32B32Sfloat:
        return sizeof(float) * 3;

      case Format::R32G32B32A32Sfloat:
        return sizeof(float) * 4;

      case Format::R8G8B8A8Unorm:
        return sizeof(uint32_t);

      default:
        throw std::runtime_error("undefined format");
    }
  }

  void createVertexInputInfo(std::pair<utils::IndexT, InputBindingInfo> const& bindingInfo,
      std::vector<vk::VertexInputBindingDescription>& bindings,
      std::vector<vk::VertexInputAttributeDescription>& attributes)
  {
    bindings.emplace_back(static_cast<uint32_t>(bindingInfo.first), static_cast<uint32_t>(bindingInfo.second.stride),
        toVkVertexInputRate(bindingInfo.second.rate));

    for (auto const& attrib : bindingInfo.second.attributes)
    {
      attributes.emplace_back(static_cast<uint32_t>(attrib.first), static_cast<uint32_t>(bindingInfo.first),
          static_cast<vk::Format>(attrib.second.format), static_cast<uint32_t>(attrib.second.offset));
    }
  }

  void genVertexInputInfo(std::pair<utils::IndexT, InputBindingInfo> const& bindingInfo,
      std::vector<vk::VertexInputBindingDescription>& bindings,
      std::vector<vk::VertexInputAttributeDescription>& attributes)
  {
    utils::SizeT stride = 0;

    for (auto const& attrib : bindingInfo.second.attributes)
    {
      attributes.emplace_back(static_cast<uint32_t>(attrib.first), static_cast<uint32_t>(bindingInfo.first),
          static_cast<vk::Format>(attrib.second.format), static_cast<uint32_t>(stride));
      stride += formatSize(attrib.second.format);
    }

    bindings.emplace_back(static_cast<uint32_t>(bindingInfo.first), static_cast<uint32_t>(stride),
        toVkVertexInputRate(bindingInfo.second.rate));
  }

  // VertexInputStateImpl ---------------------------------------------------------------------------------------------

  VertexInputStateImpl::VertexInputStateImpl(std::shared_ptr<DeviceImpl> device, VertexInputStateCreateFlags const&)
      : device_(std::move(device))
  {
  }

  void VertexInputStateImpl::addInputBinding(VertexInputRate rate)
  {
    needUpdate_ = true;

    ++currentBinding_;
    inputInfo_.insert({currentBinding_, {rate}});
  }

  void VertexInputStateImpl::addInputBinding(utils::SizeT stride, VertexInputRate rate)
  {
    needUpdate_ = true;

    ++currentBinding_;
    inputInfo_.insert({currentBinding_, {rate, stride}});
  }

  void VertexInputStateImpl::addInputAttribute(Format format)
  {
    needUpdate_ = true;

    auto& info = inputInfo_.at(currentBinding_);
    ++info.currentLocation_;
    info.attributes.insert({info.currentLocation_, {format}});
  }

  void VertexInputStateImpl::addInputAttribute(Format format, utils::OffsetT offset)
  {
    needUpdate_ = true;

    auto& info = inputInfo_.at(currentBinding_);
    ++info.currentLocation_;
    info.attributes.insert({info.currentLocation_, {format, offset}});
  }

  void VertexInputStateImpl::addInputAttribute(utils::IndexT binding, Format format, utils::OffsetT offset)
  {
    needUpdate_ = true;

    auto& info = inputInfo_.at(binding);
    ++info.currentLocation_;
    info.attributes.insert({binding, {format, offset}});
  }

  void VertexInputStateImpl::setInputBinding(utils::IndexT binding, utils::SizeT stride, VertexInputRate rate)
  {
    needUpdate_ = true;
    currentBinding_ = std::max(binding, currentBinding_);

    inputInfo_[binding].stride = stride;
    inputInfo_[binding].rate = rate;
  }

  void VertexInputStateImpl::setInputAttribute(
      utils::IndexT binding, utils::IndexT location, Format format, utils::OffsetT offset)
  {
    needUpdate_ = true;
    auto& info = inputInfo_.at(binding);
    info.currentLocation_ = std::max(location, info.currentLocation_);

    info.attributes[location].format = format;
    info.attributes[location].offset = offset;
  }

  void VertexInputStateImpl::eraseInputBinding(utils::IndexT binding)
  {
    needUpdate_ = true;
    inputInfo_.erase(binding);
  }

  void VertexInputStateImpl::eraseInputAttribute(utils::IndexT binding, utils::IndexT location)
  {
    needUpdate_ = true;
    inputInfo_.at(binding).attributes.erase(location);
  }

  void VertexInputStateImpl::update()
  {
    if (needUpdate_)
    {
      VezVertexInputFormatCreateInfo createInfo = {};
      std::vector<vk::VertexInputBindingDescription> bindings;
      std::vector<vk::VertexInputAttributeDescription> attributes;

      for (auto const& binding : inputInfo_)
      {
        if (binding.second.stride)
        {
          createVertexInputInfo(binding, bindings, attributes);
        }
        else
        {
          genVertexInputInfo(binding, bindings, attributes);
        }
      }

      createInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindings.size());
      createInfo.pVertexBindingDescriptions = reinterpret_cast<VkVertexInputBindingDescription const*>(bindings.data());
      createInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributes.size());
      createInfo.pVertexAttributeDescriptions =
          reinterpret_cast<VkVertexInputAttributeDescription const*>(attributes.data());

      checkResult(vezCreateVertexInputFormat(device_->getVkDevice(), &createInfo, &vkVertexInputFormat_));
    }
    needUpdate_ = false;
  }

  // VertexInputState -------------------------------------------------------------------------------------------------

  VertexInputState::VertexInputState(Device const& device, VertexInputStateCreateFlags const& createFlags)
      : pimpl_(std::make_shared<VertexInputStateImpl>(device.getImpl(), createFlags))
  {
  }

  void VertexInputState::addInputBinding(VertexInputRate rate)
  {
    pimpl_->addInputBinding(rate);
  }

  void VertexInputState::addInputBinding(utils::SizeT stride, VertexInputRate rate)
  {
    pimpl_->addInputBinding(stride, rate);
  }

  void VertexInputState::addInputAttribute(Format format)
  {
    pimpl_->addInputAttribute(format);
  }

  void VertexInputState::addInputAttribute(Format format, utils::OffsetT offset)
  {
    pimpl_->addInputAttribute(format, offset);
  }

  void VertexInputState::addInputAttribute(utils::IndexT binding, Format format, utils::OffsetT offset)
  {
    pimpl_->addInputAttribute(binding, format, offset);
  }

  void VertexInputState::setInputBinding(utils::IndexT binding, utils::SizeT stride, VertexInputRate rate)
  {
    pimpl_->setInputBinding(binding, stride, rate);
  }

  void VertexInputState::setInputAttribute(
      utils::IndexT binding, utils::IndexT location, Format format, utils::OffsetT offset)
  {
    pimpl_->setInputAttribute(binding, location, format, offset);
  }

  void VertexInputState::removeInputBinding(utils::IndexT binding)
  {
    pimpl_->eraseInputBinding(binding);
  }

  void VertexInputState::removeInputAttribute(utils::IndexT binding, utils::IndexT location)
  {
    pimpl_->eraseInputAttribute(binding, location);
  }

}  // namespace vulkan