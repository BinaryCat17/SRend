#pragma once
#include <filesystem>
#include <glm/glm.hpp>
#include <set>
#include <utils/signals.hpp>
#include <variant>
#include <vulkan/core.hpp>
#include <vulkan/presentation.hpp>

namespace render
{
  // Texture ----------------------------------------------------------------------------------------------------------

  enum class TextureOp
  {
    Multiply = 0x0,
    Add = 0x1,
    Subtract = 0x2,
    Divide = 0x3,
    SmoothAdd = 0x4,
    SignedAdd = 0x5,
  };

  class TextureImpl;

  class Texture
  {
   public:
    explicit Texture(std::shared_ptr<TextureImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<TextureImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit Texture(vulkan::Device const& device, std::filesystem::path const& path);

    void update();

    explicit Texture(vulkan::Device& device, void const* pData, vulkan::Format format,
    utils::Extent2D const& extent, utils::SizeT size);

   private:
    std::shared_ptr<TextureImpl> pimpl_;
  };

  // MaterialData -----------------------------------------------------------------------------------------------------

  enum class ShadingModel
  {
    Flat = 0x1,
    Gouraud = 0x2,
    Phong = 0x3,
    Blinn = 0x4,
    Toon = 0x5,
    OrenNayar = 0x6,
    Minnaert = 0x7,
    CookTorrance = 0x8,
    NoShading = 0x9,
    Fresnel = 0xa,
  };

  enum class BlendMode
  {
    Default = 0x0,
    Additive = 0x1,
  };

  class MaterialDataImpl;

  class MaterialData
  {
   public:
    explicit MaterialData(std::shared_ptr<MaterialDataImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<MaterialDataImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit MaterialData(vulkan::Device const& device);

    [[nodiscard]] std::string getName() const;

    void setName(std::string const& name);

    [[nodiscard]] glm::vec3 getDiffuseColor() const;

    void setDiffuseColor(glm::vec3 const& diffuseColor);

    [[nodiscard]] glm::vec3 getSpecularColor() const;

    void setSpecularColor(glm::vec3 const& specularColor);

    [[nodiscard]] glm::vec3 getAmbientColor() const;

    void setAmbientColor(glm::vec3 const& ambientColor);

    [[nodiscard]] glm::vec3 getTransparentColor() const;

    void setTransparentColor(glm::vec3 const& transparentColor);

    [[nodiscard]] bool isWireframe() const;

    void setWireframe(bool wireframe);

    [[nodiscard]] bool isTwoSided() const;

    void setTwoSided(bool twoSided);

    [[nodiscard]] ShadingModel getShadingModel() const;

    void setShadingModel(ShadingModel shadingModel);

    [[nodiscard]] BlendMode getBlendMode() const;

    void setBlendMode(BlendMode blendMode);

    [[nodiscard]] float getOpacity() const;

    void setOpacity(float opacity);

    [[nodiscard]] float getShininess() const;

    void setShininess(float shininess);

    [[nodiscard]] float getShininessStrength() const;

    void setShininessStrength(float shininessStrength);

   private:
    std::shared_ptr<MaterialDataImpl> pimpl_;
  };

  // Material ---------------------------------------------------------------------------------------------------------

  class MaterialImpl;

  class Material
  {
   public:
    explicit Material(std::shared_ptr<MaterialImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<MaterialImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit Material(vulkan::Device const& device, MaterialData const& materialData);

    void setMaterialData(MaterialData const& material);

    [[nodiscard]] MaterialData getMaterialData() const;

    [[nodiscard]] utils::SizeT getDiffuseTextureCount() const;

    void addDiffuseTexture(Texture const& texture, float blendFactor = 1.0f, TextureOp op = TextureOp::Add);

    void removeDiffuseTexture(utils::IndexT index);

    [[nodiscard]] Texture getDiffuseTexture(utils::IndexT index) const;

    [[nodiscard]] float getDiffuseTextureBlendFactor(utils::IndexT index) const;

    [[nodiscard]] TextureOp getDiffuseTextureOp(utils::IndexT index) const;

    [[nodiscard]] utils::SizeT getSpecularTextureCount() const;

    void addSpecularTexture(Texture const& texture, float blendFactor = 1.0f, TextureOp op = TextureOp::Add);

    void removeSpecularTexture(utils::IndexT index);

    [[nodiscard]] Texture getSpecularTexture(utils::IndexT index) const;

    [[nodiscard]] float getSpecularTextureBlendFactor(utils::IndexT index) const;

    [[nodiscard]] TextureOp getSpecularTextureOp(utils::IndexT index) const;

    [[nodiscard]] utils::SizeT getAmbientTextureCount() const;

    void addAmbientTexture(Texture const& texture, float blendFactor = 1.0f, TextureOp op = TextureOp::Add);

    void removeAmbientTexture(utils::IndexT index);

    [[nodiscard]] Texture getAmbientTexture(utils::IndexT index) const;

    [[nodiscard]] float getAmbientTextureBlendFactor(utils::IndexT index) const;

    [[nodiscard]] TextureOp getAmbientTextureOp(utils::IndexT index) const;

   private:
    std::shared_ptr<MaterialImpl> pimpl_;
  };

  // Mesh -------------------------------------------------------------------------------------------------------------

  class MeshImpl;

  class Mesh
  {
   public:
    explicit Mesh(std::shared_ptr<MeshImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<MeshImpl> getImpl() const
    {
      return pimpl_;
    }

    [[nodiscard]] std::string getName() const;

    void setName(std::string const& name);

   private:
    std::shared_ptr<MeshImpl> pimpl_;
  };

  // Object -----------------------------------------------------------------------------------------------------------

  class ObjectImpl;

  class Object
  {
   public:
    explicit Object(std::shared_ptr<ObjectImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<ObjectImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit Object(vulkan::Device const& device, Mesh const& mesh, Material const& material);

    void operator()(vulkan::CommandBuffer& commandBuffer) const;

    [[nodiscard]] Mesh getMesh() const;

    [[nodiscard]] Material getMaterial() const;

    [[nodiscard]] std::string getName() const;

    void setPosition(glm::vec3 const& pos);

    void setRotation(glm::vec3 const& rotation);

    void setScale(glm::vec3 const& scale);

    [[nodiscard]] glm::vec3 getPosition() const;

    [[nodiscard]] glm::vec3 getRotation() const;

    [[nodiscard]] glm::vec3 getScale() const;

    void translate(glm::vec3 const& pos);

    void rotate(glm::vec3 const& rotation);

    void scale(glm::vec3 const& scale);

    [[nodiscard]] glm::mat4 getTransform() const;

    friend bool operator<(Object const& lhs, Object const& rhs)
    {
      return lhs.pimpl_ < rhs.pimpl_;
    }
    friend bool operator>(Object const& lhs, Object const& rhs)
    {
      return rhs < lhs;
    }
    friend bool operator<=(Object const& lhs, Object const& rhs)
    {
      return !(rhs < lhs);
    }
    friend bool operator>=(Object const& lhs, Object const& rhs)
    {
      return !(lhs < rhs);
    }

   private:
    std::shared_ptr<ObjectImpl> pimpl_;
  };

  // Light ------------------------------------------------------------------------------------------------------------

  class LightImpl;

  class Light
  {
   public:
    explicit Light(std::shared_ptr<LightImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<LightImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit Light(vulkan::Device const& device);

    void operator()(vulkan::CommandBuffer& commandBuffer) const;

    void setPosition(glm::vec3 const& pos);

    [[nodiscard]] glm::vec3 getPosition() const;

    void setIntensity(glm::vec3 intensity);

    [[nodiscard]] glm::vec3 getIntensity() const;

   private:
    std::shared_ptr<LightImpl> pimpl_;
  };

  // Camera -----------------------------------------------------------------------------------------------------------

  class CameraImpl;

  class Camera
  {
   public:
    explicit Camera(std::shared_ptr<CameraImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<CameraImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit Camera(vulkan::Device const& device, utils::Viewport const& viewport);

    void operator()(vulkan::CommandBuffer& commandBuffer) const;

    void setPosition(glm::vec3 const& pos);

    void setRotation(glm::vec3 const& pos);

    void setViewport(utils::Viewport const& viewport);

    [[nodiscard]] glm::vec3 getRotation() const;

    [[nodiscard]] glm::vec3 getPosition() const;

    [[nodiscard]] vulkan::Viewport getViewport() const;

    void update();

   private:
    std::shared_ptr<CameraImpl> pimpl_;
  };

  // Gui --------------------------------------------------------------------------------------------------------------

  class GuiImpl;

  class Gui
  {
   public:
    explicit Gui(std::shared_ptr<GuiImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<GuiImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit Gui(vulkan::Device const& device, wsystem::Window const& window);

    void operator()(vulkan::CommandBuffer& commandBuffer);

   private:
    std::shared_ptr<GuiImpl> pimpl_;
  };

  // Collection -------------------------------------------------------------------------------------------------------

  class CollectionImpl;

  class Collection
  {
   public:
    using iterator = std::set<std::variant<Object, Collection>>::iterator;
    using const_iterator = std::set<std::variant<Object, Collection>>::const_iterator;

    explicit Collection(std::shared_ptr<CollectionImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<CollectionImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit Collection(vulkan::Device const& device, std::string const& name);

    void operator()(vulkan::CommandBuffer& commandBuffer) const;

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] utils::SizeT size() const;

    void insert(std::variant<Object, Collection> const& obj);

    void erase(std::variant<Object, Collection> const& obj);

    [[nodiscard]] iterator begin();

    [[nodiscard]] const_iterator begin() const;

    [[nodiscard]] iterator end();

    [[nodiscard]] const_iterator end() const;

    void setPosition(glm::vec3 pos);

    void setRotation(glm::vec3 rotation);

    void setScale(glm::vec3 scale);

    void translate(glm::vec3 const& pos);

    void rotate(glm::vec3 const& rotation);

    void scale(glm::vec3 const& scale);

    [[nodiscard]] glm::vec3 getPosition() const;

    [[nodiscard]] glm::vec3 getRotation() const;

    [[nodiscard]] glm::vec3 getScale() const;

    [[nodiscard]] glm::mat4 getTransform() const;

    friend bool operator<(Collection const& lhs, Collection const& rhs)
    {
      return lhs.pimpl_ < rhs.pimpl_;
    }
    friend bool operator>(Collection const& lhs, Collection const& rhs)
    {
      return rhs < lhs;
    }
    friend bool operator<=(Collection const& lhs, Collection const& rhs)
    {
      return !(rhs < lhs);
    }
    friend bool operator>=(Collection const& lhs, Collection const& rhs)
    {
      return !(lhs < rhs);
    }

   private:
    std::shared_ptr<CollectionImpl> pimpl_;
  };

  // Scene ------------------------------------------------------------------------------------------------------------

  class SceneImpl;

  class Scene
  {
   public:
    explicit Scene(std::shared_ptr<SceneImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<SceneImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit Scene(vulkan::Device const& device, std::filesystem::path const& path);

    void operator()(vulkan::CommandBuffer& commandBuffer) const;

    void load();

    [[nodiscard]] Collection getMembers() const;

    [[nodiscard]] std::vector<Mesh> const& getMeshes() const;

    [[nodiscard]] std::vector<Light> const& getLights() const;

    [[nodiscard]] std::vector<Material> const& getMaterials() const;

   private:
    std::shared_ptr<SceneImpl> pimpl_;
  };

  // Render -----------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(RenderCreate, {};)

  // clang-format on

  using Command = utils::signals::Connection<void(vulkan::CommandBuffer&)>;

  class RenderImpl;

  class Render
  {
   public:
    explicit Render(std::shared_ptr<RenderImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<RenderImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit Render(
        vulkan::Device const& device, RenderCreateFlags const& createFlags, vulkan::Image const& attachment);

    Command record(std::function<void(vulkan::CommandBuffer&)> const& obj);

    void erase(Command const& command);

    Command recordPostCommand(std::function<void(vulkan::CommandBuffer&)> const& obj);

    void erasePostCommand(Command const& command);

    vulkan::Semaphore render(std::vector<vulkan::WaitInfo> const& waitInfos);

   private:
    std::shared_ptr<RenderImpl> pimpl_;
  };

  // Presenter --------------------------------------------------------------------------------------------------------

  class PresenterImpl;

  class Presenter
  {
   public:
    explicit Presenter(std::shared_ptr<PresenterImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<PresenterImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit Presenter(
        vulkan::Device const& device, utils::Extent2D const& extent);

    Command record(std::function<void(vulkan::CommandBuffer&)> const& obj);

    void erase(Command const& command);

    Command recordPostCommand(std::function<void(vulkan::CommandBuffer&)> const& obj);

    void erasePostCommand(Command const& command);

    void runLoop();

    [[nodiscard]] wsystem::Window getWindow() const;

   private:
    std::shared_ptr<PresenterImpl> pimpl_;
  };

}  // namespace render