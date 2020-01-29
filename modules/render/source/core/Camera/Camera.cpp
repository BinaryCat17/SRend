#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <queue>
#include "../../../include/render/core.hpp"
#include "SDL.h"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  void updateCamera(ShaderCameraData& camera, vulkan::Viewport const& viewport, glm::vec3 const& pos, glm::vec3 front)
  {
    camera.viewMatrix = glm::lookAt(pos, pos + front, {0.f, 0.f, 1.f});

    auto extent = viewport.getExtent();
    camera.projectionMatrix = glm::perspective(glm::radians(45.0f), extent.width() / extent.height(), 0.1f, 1000.0f);
    camera.projectionMatrix[1][1] *= -1;
  }

  vulkan::Viewport createVulkanViewport(vulkan::Device const& device, utils::Viewport viewport)
  {
    vulkan::Viewport result(device);
    result.setViewport(viewport);
    return result;
  }

  // CameraImpl -------------------------------------------------------------------------------------------------------

  CameraImpl::CameraImpl(vulkan::Device device, utils::Viewport viewport)
      : buffer_(createUniformBuffer(device, nullptr, sizeof(ShaderCameraData))),
        data_(buffer_.mapMemory(buffer_.getSize())),
        viewport_(createVulkanViewport(device, viewport)),
        pos_(glm::vec3(0, 0, 0)),
        rotation_(glm::vec3(0, 0, 0))
  {
    updateCamera(*data_.pT<ShaderCameraData>(), viewport_, pos_, front_);
  }

  void CameraImpl::operator()(vulkan::CommandBuffer& commandBuffer) const
  {
    commandBuffer.bindBuffer(buffer_, vulkan::BindingInfo(9));
  }

  void CameraImpl::setPosition(glm::vec3 const& pos)
  {
    if (pos_ != pos)
    {
      pos_ = pos;
      updateCamera(*data_.pT<ShaderCameraData>(), viewport_, pos_, front_);
    }
  }

  void CameraImpl::setRotation(glm::vec3 const& rotation)
  {
    if (rotation_ != rotation)
    {
      rotation_ = rotation;
      updateCamera(*data_.pT<ShaderCameraData>(), viewport_, pos_, front_);
    }
  }

  void CameraImpl::setViewport(utils::Viewport const& viewport)
  {
    if (viewport_.getViewport() != viewport)
    {
      viewport_.setViewport(viewport);
      updateCamera(*data_.pT<ShaderCameraData>(), viewport_, pos_, front_);
    }
  }

  void CameraImpl::update()
  {
    front_.x = cos(glm::radians(rotation_.x)) * cos(glm::radians(rotation_.z));
    front_.z = sin(glm::radians(rotation_.z));
    front_.y = sin(glm::radians(rotation_.x)) * cos(glm::radians(rotation_.z));
    front_ = glm::normalize(front_);
    glm::vec3 rightVec = glm::normalize(glm::cross(front_, glm::vec3(0, 0, 1)));
    float velocity = speed_;

    std::vector<SDL_Event> pushEvents;
    SDL_Event event_ = {};
    static  bool inMode = false;

    while (SDL_PollEvent(&event_))
    {
      if (event_.type == SDL_KEYDOWN)
      {
        if (event_.key.keysym.sym == SDLK_ESCAPE)
        {
          inMode = !inMode;
          if(inMode)
          {
            SDL_SetRelativeMouseMode(SDL_TRUE);
          }
          else
          {
            SDL_SetRelativeMouseMode(SDL_FALSE);
          }
        }
        else if (event_.key.keysym.sym == SDLK_UP && inMode)
          pos_ += glm::vec3(front_) * velocity;
        else if (event_.key.keysym.sym == SDLK_DOWN && inMode)
          pos_ -= glm::vec3(front_) * velocity;
        else if (event_.key.keysym.sym == SDLK_LEFT && inMode)
          pos_ -= rightVec * velocity;
        else if (event_.key.keysym.sym == SDLK_RIGHT && inMode)
          pos_ += rightVec * velocity;
        else
        {
          pushEvents.push_back(event_);
        }
      }
      else if (event_.type == SDL_MOUSEMOTION && inMode)
      {
        auto xoffset = event_.motion.xrel;
        auto yoffset = event_.motion.yrel;

        rotation_.x -= xoffset;
        rotation_.z -= yoffset;

        if (rotation_.z > 89.0f)
          rotation_.z = 89.0f;
        if (rotation_.z< -89.0f)
          rotation_.z = -89.0f;
      }
    }

    for (auto& event : pushEvents)
    {
      SDL_PushEvent(&event);
    }

    updateCamera(*data_.pT<ShaderCameraData>(), viewport_, pos_, front_);
  }  // namespace render

  // Camera -----------------------------------------------------------------------------------------------------------

  Camera::Camera(vulkan::Device const& device, utils::Viewport const& viewport)
      : pimpl_(std::make_shared<CameraImpl>(device, viewport))
  {
  }

  void Camera::operator()(vulkan::CommandBuffer& commandBuffer) const
  {
    pimpl_->operator()(commandBuffer);
  }

  void Camera::setPosition(glm::vec3 const& pos)
  {
    pimpl_->setPosition(pos);
  }

  void Camera::setViewport(utils::Viewport const& viewport)
  {
    pimpl_->setViewport(viewport);
  }

  [[nodiscard]] glm::vec3 Camera::getPosition() const
  {
    return pimpl_->getPosition();
  }

  [[nodiscard]] vulkan::Viewport Camera::getViewport() const
  {
    return pimpl_->getViewport();
  }

  void Camera::setRotation(glm::vec3 const& pos)
  {
    pimpl_->setRotation(pos);
  }

  glm::vec3 Camera::getRotation() const
  {
    return pimpl_->getRotation();
  }

  void Camera::update()
  {
    pimpl_->update();
  }

}  // namespace render