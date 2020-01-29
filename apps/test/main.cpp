#include <imgui.h>
#include <imgui-filebrowser/imfilebrowser.h>
#include <iostream>
#include <render/core.hpp>
#include <vulkan/presentation.hpp>

vulkan::Application createApplication()
{
  return vulkan::Application({}, {}, vulkan::ExtensionsFlagBits::Presentation,
      { vulkan::ValidationLayersFlagBits::StandardValidation},
      utils::debug::Messenger(utils::debug::MessageSeverityFlagBits::error |
                              utils::debug::MessageSeverityFlagBits::warning |
                              utils::debug::MessageSeverityFlagBits::notice));
}

vulkan::Device createDevice(vulkan::Application const& application)
{
  auto physicalDevices = application.getSupportedPhysicalDevices();

  std::cout << "Supported physical devices : " << std::endl;

  for (auto const& physicalDevice : physicalDevices)
  {
    using namespace magic_enum::ostream_operators;

    std::cout << "\tPhysical device : " << physicalDevice.name() << ". Type : " << physicalDevice.type() << "."
              << std::endl;

    if (!physicalDevices.empty())
    {
      std::cout << "Selected physical device : " << physicalDevices[0].name() << "." << std::endl;
      return vulkan::Device(application, {}, physicalDevices[0]);
    }
  }
  throw std::runtime_error("no physical device supports vulkan");
}

using Collector = utils::signals::Signal<void(vulkan::CommandBuffer&)>;
struct RenderObjects
{
  render::Camera camera;
  render::Light light;
  std::vector<render::Scene> scenes_;
  Collector collector_;
  Collector postCollector_;
};

RenderObjects createRenderObjects(render::Presenter& presenter, vulkan::Device& device, utils::Extent2D const& extent)
{
  render::Camera camera(device, utils::Viewport(extent));
  presenter.getWindow().onResize().connect([presenter, camera] {
    auto cam = camera;
    cam.setViewport(utils::Viewport(presenter.getWindow().getSize()));
  });

  camera.setPosition(glm::vec3(10, 10, 10));
  presenter.record([presenter, camera](vulkan::CommandBuffer&){ auto copyCamera = camera; copyCamera.update(); });
  presenter.record(camera);

  render::Light light(device);
  light.setPosition(glm::vec3(-10, -10, 55));
  light.setIntensity(glm::vec3(1, 1, 1));
  presenter.record(light);

  Collector collector;
  presenter.record(collector);

  Collector postCollector;
  presenter.recordPostCommand(postCollector);

  RenderObjects objects{camera, light, {}, collector, postCollector};
  return objects;
}

template <typename T>
void recordObject(T val)
{
  ImGui::Text("Transform");

  auto pos = val.getPosition();
  ImGui::DragFloat3("Position", &pos[0]);
  val.setPosition(pos);

  auto rotation = val.getRotation();
  ImGui::DragFloat3("Rotation", &rotation[0]);
  val.setRotation(rotation);

  glm::vec3 scale = val.getScale();
  ImGui::DragFloat3("Scale", &scale[0]);
  val.setScale(scale);
}

using RenderObject = std::variant<render::Object, render::Collection>;

void recordGuiScene(
    render::Collection::iterator begin, render::Collection::iterator end, std::optional<RenderObject>& currentObj)
{
  utils::SizeT i = 0;

  for (; begin != end; ++begin)
  {
    ++i;
    std::visit(
        [i, &currentObj](auto&& val) {
          using T = std::decay_t<decltype(val)>;

          if constexpr (std::is_same_v<T, render::Object>)
          {
            if (ImGui::Button(std::string("Object " + std::to_string(i)).c_str()))
            {
              currentObj = val;
            }
          }
          else if constexpr (std::is_same_v<T, render::Collection>)
          {
            if (ImGui::TreeNode(std::string("Collection" + std::to_string(i)).c_str()))
            {
              if (ImGui::Button("Select All"))
              {
                currentObj = val;
              }
              recordGuiScene(val.begin(), val.end(), currentObj);
              ImGui::TreePop();
            }
          }
        },
        *begin);
  }
}

void recordCamera(render::Camera camera)
{
  ImGui::Text("Camera");
  glm::vec3 cameraPos = camera.getPosition();
  ImGui::DragFloat3("Position", &cameraPos[0]);
  camera.setPosition(cameraPos);

  glm::vec3 rotation = camera.getRotation();
  ImGui::DragFloat3("Rotation", &rotation[0]);
  camera.setRotation(rotation);
}

void recordLight(render::Light light)
{
  ImGui::Text("Light");
  glm::vec3 lightColor = light.getIntensity();
  ImGui::ColorEdit3("LightColor", &lightColor[0]);
  light.setIntensity(lightColor);

  glm::vec3 lightPos = light.getPosition();
  ImGui::DragFloat3("LightPos", &lightPos[0]);
  light.setPosition(lightPos);
}

void recordMaterial(vulkan::Device device_, render::Presenter presenter, render::Material material)
{
  if (ImGui::TreeNode(std::string("Material : " + material.getMaterialData().getName()).c_str()))
  {
    glm::vec3 diffuseColor = material.getMaterialData().getDiffuseColor();
    ImGui::ColorEdit3("DiffuseColor", &diffuseColor[0]);
    material.getMaterialData().setDiffuseColor(diffuseColor);

    glm::vec3 ambientColor = material.getMaterialData().getAmbientColor();
    ImGui::ColorEdit3("AmbientColor", &ambientColor[0]);
    material.getMaterialData().setAmbientColor(ambientColor);

    glm::vec3 specularColor = material.getMaterialData().getSpecularColor();
    ImGui::ColorEdit3("SpecularColor", &specularColor[0]);
    material.getMaterialData().setSpecularColor(specularColor);

    glm::vec3 transparentColor = material.getMaterialData().getTransparentColor();
    ImGui::ColorEdit3("TransparentColor", &transparentColor[0]);
    material.getMaterialData().setTransparentColor(transparentColor);

    float shininess = material.getMaterialData().getShininess();
    ImGui::DragFloat("Shininess", &shininess);
    material.getMaterialData().setShininess(shininess);

    float shininessStrength = material.getMaterialData().getShininessStrength();
    ImGui::DragFloat("ShininessStrength", &shininessStrength);
    material.getMaterialData().setShininessStrength(shininessStrength);

    float opacity = material.getMaterialData().getOpacity();
    ImGui::DragFloat("Opacity", &opacity);
    material.getMaterialData().setOpacity(opacity);

    ImGui::Text("ShadingMode");

    int shadingModel = static_cast<int>(material.getMaterialData().getShadingModel());

    ImGui::RadioButton("Flat", &shadingModel, static_cast<int>(render::ShadingModel::Flat));
    ImGui::RadioButton("Phong", &shadingModel, static_cast<int>(render::ShadingModel::Phong));
    ImGui::RadioButton("Toon", &shadingModel, static_cast<int>(render::ShadingModel::Toon));
    material.getMaterialData().setShadingModel(static_cast<render::ShadingModel>(shadingModel));

    //

    static ImGui::FileBrowser fileDialog;
    fileDialog.SetTitle("File-browser");
    if (ImGui::Button("Load texture from file")) fileDialog.Open();
    fileDialog.Display();
    if (fileDialog.HasSelected())
    {
      render::Texture texture(device_, fileDialog.GetSelected().string());
      material.addDiffuseTexture(texture);
      presenter.recordPostCommand([texture](vulkan::CommandBuffer&){
        auto cloneTexture = texture; cloneTexture.update(); });

      fileDialog.ClearSelected();
    }

    ImGui::TreePop();
  }
}

void recordToolWindow(
    vulkan::Device& device, render::Presenter presenter, RenderObjects& objects, std::optional<RenderObject>& currObj)
{
  ImGui::Begin("Tool window");

  recordCamera(objects.camera);
  recordLight(objects.light);




  if (ImGui::TreeNode("Current object"))
  {
    if (currObj)
    {
      std::visit(
          []<typename T>(T val) { recordObject(val); }, *currObj);
    }
    ImGui::TreePop();
  }

  static ImGui::FileBrowser fileDialog;
  fileDialog.SetTitle("File-browser");
  if (ImGui::Button("Load scene from file")) fileDialog.Open();

  fileDialog.Display();

  if (fileDialog.HasSelected())
  {
    render::Scene scene(device, fileDialog.GetSelected().string());
    scene.getMembers().setRotation(glm::vec3(90, 90, 0));
    objects.scenes_.push_back(scene);
    objects.collector_.connect(scene);
    objects.postCollector_.connect([scene](vulkan::CommandBuffer&) {
      render::Scene copyScene = scene;
      copyScene.load();
    });
    fileDialog.ClearSelected();
  }

  ImGui::End();
}

void recordSceneViewer(vulkan::Device device, std::vector<render::Scene> const& scenes,
    std::optional<RenderObject>& currentObject, render::Presenter presenter)
{
  ImGui::Begin("Scene viewer");

  for (auto const& scene : scenes)
  {
    auto members = scene.getMembers();
    if (ImGui::TreeNode(std::string("Scene : " + members.getName()).c_str()))
    {
      if (ImGui::CollapsingHeader("Objects"))
      {
        if (ImGui::Button("Select All"))
        {
          currentObject = members;
        }
        recordGuiScene(members.begin(), members.end(), currentObject);
      }

      if (ImGui::CollapsingHeader("Materials"))
      {
        for (render::Material const& material : scene.getMaterials())
        {
          recordMaterial(device,presenter, material);
        }
      }

      ImGui::TreePop();
    }
  }

  ImGui::End();
}

void recordGui(render::Presenter& presenter, vulkan::Device device, RenderObjects& objects)
{
  ImGui::NewFrame();

  static std::optional<RenderObject> currentObject;
  recordToolWindow(device, presenter, objects, currentObject);
  recordSceneViewer(device, objects.scenes_, currentObject, presenter);

  ImGui::Render();
}

render::Gui createGui(vulkan::Device& device, render::Presenter& presenter, RenderObjects& objects)
{
  render::Gui gui(device, presenter.getWindow());
  presenter.record([device, &objects, &presenter](vulkan::CommandBuffer&) { recordGui(presenter, device, objects); });
  presenter.record(gui);
  return gui;
}

int main()
{
  try
  {
    auto application = createApplication();
    auto device = createDevice(application);
    auto extent = utils::Extent2D(1600, 1000);
    render::Presenter presenter(device, extent);
    auto objects = createRenderObjects(presenter, device, extent);
    auto gui = createGui(device, presenter, objects);
    presenter.runLoop();
  }
  catch (std::exception const& ex)
  {
    std::cerr << "ERROR : " << ex.what() << std::endl;
  }
  system("pause");
}
