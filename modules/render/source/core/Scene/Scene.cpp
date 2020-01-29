#include "Scene.hpp"
#include <assimp/postprocess.h>
#include "../../../include/render/core.hpp"
#include "../Collection/Collection.hpp"
#include "../Light/Light.hpp"
#include "../Material/Material.hpp"
#include "../Mesh/Mesh.hpp"
#include "../Object/Object.hpp"

namespace render
{
  // utils ------------------------------------------------------------------------------------------------------------

  aiScene const* createAiScene(Assimp::Importer& importer, std::filesystem::path const& path)
  {
    aiScene const* scene =
        importer.ReadFile(path.string(), aiProcessPreset_TargetRealtime_Quality | aiProcess_PreTransformVertices);
    if (!scene)
    {
      throw std::runtime_error(importer.GetErrorString());
    }

    return scene;
  }

  void getObjects(Collection& result, vulkan::Device& device, aiNode const& node, aiScene const* aiScene,
      std::vector<Mesh> const& meshes, std::vector<Material> const& materials)
  {
    for (utils::IndexT i = 0; i != node.mNumMeshes; ++i)
    {
      auto mesh = meshes[node.mMeshes[i]];

      result.insert(Object(
          std::make_shared<ObjectImpl>(device, mesh, materials[aiScene->mMeshes[node.mMeshes[i]]->mMaterialIndex])));
    }

    for (utils::IndexT i = 0; i != node.mNumChildren; ++i)
    {
      Collection collection(std::make_shared<CollectionImpl>(node.mChildren[i]->mName.data));
      getObjects(collection, device, *node.mChildren[i], aiScene, meshes, materials);
      result.insert(collection);
    }
  }

  std::vector<Light> createLights(vulkan::Device& device, aiScene const& scene)
  {
    std::vector<Light> result;

    for (utils::IndexT i = 0; i != scene.mNumLights; ++i)
    {
      glm::vec3 pos = {scene.mLights[i]->mPosition.x, scene.mLights[i]->mPosition.y, scene.mLights[i]->mPosition.z};
      glm::vec3 color = {
          scene.mLights[i]->mColorDiffuse.r, scene.mLights[i]->mColorDiffuse.g, scene.mLights[i]->mColorDiffuse.b};

      result.emplace_back(std::make_shared<LightImpl>(device));
      result.back().setPosition(pos);
      result.back().setIntensity(color);
    }

    return result;
  }

  std::vector<Mesh> createMeshes(vulkan::Device& device, aiScene const& scene)
  {
    std::vector<Mesh> result;

    for (utils::IndexT i = 0; i != scene.mNumMeshes; ++i)
    {
      result.emplace_back(std::make_shared<MeshImpl>(device, *scene.mMeshes[i]));
    }

    return result;
  }

  std::vector<Material> createMaterials(vulkan::Device& device, aiScene const& scene)
  {
    std::vector<Material> result;

    for (utils::IndexT i = 0; i != scene.mNumMaterials; ++i)
    {
      result.emplace_back(std::make_shared<MaterialImpl>(device, *scene.mMaterials[i]));
    }

    return result;
  }

  // SceneImpl --------------------------------------------------------------------------------------------------------

  SceneImpl::SceneImpl(vulkan::Device device, std::filesystem::path path)
      : device_(std::move(device)), path_(std::move(path)), rootCollection_(device_, "")
  {
  }

  void SceneImpl::operator()(vulkan::CommandBuffer& commandBuffer) const
  {
    if(loaded_)
    {
      rootCollection_(commandBuffer);
    }
  }

  void SceneImpl::load()
  {
    if(!loaded_)
    {
      loaded_ = true;
      aiScene_ = createAiScene(importer_, path_);
      auto pos = rootCollection_.getPosition();
      auto rotation = rootCollection_.getRotation();
      auto scale = rootCollection_.getScale();
      rootCollection_ = Collection(std::make_shared<CollectionImpl>(aiScene_->mRootNode->mName.data));
      rootCollection_.setPosition(pos);
      rootCollection_.setRotation(rotation);
      rootCollection_.setScale(scale);
      meshes_ = createMeshes(device_, *aiScene_);
      lights_ = createLights(device_, *aiScene_);
      materials_ = createMaterials(device_, *aiScene_);
      getObjects(rootCollection_, device_, *aiScene_->mRootNode, aiScene_, meshes_, materials_);
    }
  }

  // Scene ------------------------------------------------------------------------------------------------------------

  Scene::Scene(vulkan::Device const& device, std::filesystem::path const& path)
      : pimpl_(std::make_shared<SceneImpl>(device, path))
  {
  }

  [[nodiscard]] Collection Scene::getMembers() const
  {
    return pimpl_->getMembers();
  }

  [[nodiscard]] std::vector<Mesh> const& Scene::getMeshes() const
  {
    return pimpl_->getMeshes();
  }

  [[nodiscard]] std::vector<Light> const& Scene::getLights() const
  {
    return pimpl_->getLights();
  }

  [[nodiscard]] std::vector<Material> const& Scene::getMaterials() const
  {
    return pimpl_->getMaterials();
  }

  void Scene::operator()(vulkan::CommandBuffer& commandBuffer) const
  {
    pimpl_->operator()(commandBuffer);
  }

  void Scene::load()
  {
    pimpl_->load();
  }

}  // namespace render
