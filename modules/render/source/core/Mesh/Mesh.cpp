#include "Mesh.hpp"
#include "../../../include/render/core.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  vulkan::Buffer createVertexBuffer(vulkan::Device& device, aiMesh const& mesh)
  {
    struct Vertex
    {
      glm::vec3 pos;
      glm::vec3 normal;
      glm::vec2 texCoord;
    };

    std::vector<Vertex> vertices;
    vertices.reserve(mesh.mNumVertices);

    for (utils::IndexT i = 0; i != mesh.mNumVertices; ++i)
    {
      Vertex vertex = {};
      vertex.pos = {mesh.mVertices[i].x, mesh.mVertices[i].y, mesh.mVertices[i].z};
      if (mesh.HasNormals())
      {
        vertex.normal = {mesh.mNormals[i].x, mesh.mNormals[i].y, mesh.mNormals[i].z};
      }
      if (mesh.HasTextureCoords(0))
      {
        vertex.texCoord = {mesh.mTextureCoords[0][i].x, 1.0f - mesh.mTextureCoords[0][i].y};
      }
      vertices.push_back(vertex);
    }

    return createDeviceBuffer(
        device, vulkan::BufferUsageFlagBits::VertexBuffer, vertices.data(), vertices.size() * sizeof(Vertex));
  }

  vulkan::Buffer createIndexBuffer(vulkan::Device& device, aiMesh const& mesh)
  {
    std::vector<uint32_t> indices;

    for (uint32_t f = 0; f < mesh.mNumFaces; f++)
    {
      for (uint32_t j = 0; j < mesh.mFaces[f].mNumIndices; j++)
      {
        indices.push_back(mesh.mFaces[f].mIndices[j]);
      }
    }

    return createDeviceBuffer(
        device, vulkan::BufferUsageFlagBits::IndexBuffer, indices.data(), indices.size() * sizeof(uint32_t));
  }

  // MeshImpl ---------------------------------------------------------------------------------------------------------

  MeshImpl::MeshImpl(vulkan::Device& device, aiMesh const& mesh)
      : aiMesh_(&mesh),
        name_(aiMesh_->mName.data),
        vertexBuffer_(createVertexBuffer(device, mesh)),
        indexBuffer_(createIndexBuffer(device, mesh))
  {
  }

  void MeshImpl::operator()(vulkan::CommandBuffer& commandBuffer) const
  {
    commandBuffer.bindVertexBuffer(vertexBuffer_);
    commandBuffer.bindIndexBuffer(indexBuffer_, vulkan::IndexType::Uint32);
    commandBuffer.drawIndexed(0, indexBuffer_.getSize() / sizeof(uint32_t));
  }

  // Mesh -------------------------------------------------------------------------------------------------------------

  std::string Mesh::getName() const
  {
    return pimpl_->getName();
  }

  void Mesh::setName(std::string const& name)
  {
    pimpl_->setName(name);
  }

}  // namespace render