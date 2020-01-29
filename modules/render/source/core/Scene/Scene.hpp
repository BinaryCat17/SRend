#pragma once
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include "../utils.hpp"

namespace render
{
  // SceneImpl --------------------------------------------------------------------------------------------------------

  class SceneImpl
  {
   public:
    explicit SceneImpl(vulkan::Device device, std::filesystem::path path);

    void operator()(vulkan::CommandBuffer& commandBuffer) const;

    void load();

    [[nodiscard]] aiScene const& getAiScene() const
    {
      return *aiScene_;
    }

    [[nodiscard]] Collection getMembers()
    {
      return rootCollection_;
    }

    [[nodiscard]] std::vector<Mesh> const& getMeshes() const
    {
      return meshes_;
    }

    [[nodiscard]] std::vector<Light> const& getLights() const
    {
      return lights_;
    }

    [[nodiscard]] std::vector<Material> const& getMaterials() const
    {
      return materials_;
    }

    [[nodiscard]] std::vector<Texture> const& getTextures() const
    {
      return textures_;
    }

   private:
    vulkan::Device device_;
    std::filesystem::path path_;
    Assimp::Importer importer_;
    aiScene const* aiScene_ = nullptr;
    Collection rootCollection_;
    std::vector<Mesh> meshes_;
    std::vector<Light> lights_;
    std::vector<Material> materials_;
    std::vector<Texture> textures_;
    bool loaded_ = false;
  };

}  // namespace render