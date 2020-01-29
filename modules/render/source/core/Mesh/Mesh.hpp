#pragma once
#include "../utils.hpp"
#include <assimp/mesh.h>

namespace render
{
  // MeshImpl ---------------------------------------------------------------------------------------------------------

  class MeshImpl
  {
   public:
    explicit MeshImpl(vulkan::Device& device, aiMesh const& mesh);

    void operator()(vulkan::CommandBuffer& commandBuffer) const;

    [[nodiscard]] aiMesh const* getAiMesh() const
    {
      return aiMesh_;
    }

    [[nodiscard]] std::string getName() const
    {
      return name_;
    }

    void setName(std::string name)
    {
      name_ = std::move(name);
    }

   private:
    aiMesh const* aiMesh_;
    std::string name_;
    vulkan::Buffer vertexBuffer_;
    vulkan::Buffer indexBuffer_;
  };

}  // namespace render