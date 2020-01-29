#pragma once
#include <utils/debug.hpp>
#include <utils/utils.hpp>
#include <variant>

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(SampleCount, {
    e1 = 0x00000001,
    e2 = 0x00000002,
    e4 = 0x00000004,
    e8 = 0x00000008,
    e16 = 0x00000010,
    e32 = 0x00000020,
    e64 = 0x00000040,
  };)

  SR_MAKE_BIT_FLAGS(CullMode, {
    Front = 0x00000001,
    Back = 0x00000002,
    FrontAndBlack = 0x00000003,
  };)

  SR_MAKE_BIT_FLAGS(ColorComponent, {
    R = 0x00000001,
    G = 0x00000002,
    B = 0x00000004,
    A = 0x00000008,
  };)

  SR_MAKE_BIT_FLAGS(WaitStage, {
    AllCommands = 1u << 0u,
    AllGraphics = 1u << 1u,
    TopOfPipe = 1u << 2u,
    BottomOfPipe = 1u << 3u,
    VertexInput = 1u << 4u,
    VertexShader = 1u << 5u,
    FragmentShader = 1u << 6u,
    EarlyFragmentTests = 1u << 7u,
    LateFragmentTests = 1u << 8u,
    GeometryShader = 1u << 9u,
    TessellationControlShader = 1u << 10u,
    TessellationEvaluationShader = 1u << 11u,
    ComputeShader = 1u << 12u,
    Host = 1u << 13u,
    Transfer = 1u << 14u,
    ColorAttachmentOutput = 15u << 0u
  };)

  // clang-format on

  enum class Format
  {
    Undefined = 0,
    R4G4UnormPack8 = 1,
    R4G4B4A4UnormPack16 = 2,
    B4G4R4A4UnormPack16 = 3,
    R5G6B5UnormPack16 = 4,
    B5G6R5UnormPack16 = 5,
    R5G5B5A1UnormPack16 = 6,
    B5G5R5A1UnormPack16 = 7,
    A1R5G5B5UnormPack16 = 8,
    R8Unorm = 9,
    R8Snorm = 10,
    R8Uscaled = 11,
    R8Sscaled = 12,
    R8Uint = 13,
    R8Sint = 14,
    R8Srgb = 15,
    R8G8Unorm = 16,
    R8G8Snorm = 17,
    R8G8Uscaled = 18,
    R8G8Sscaled = 19,
    R8G8Uint = 20,
    R8G8Sint = 21,
    R8G8Srgb = 22,
    R8G8B8Unorm = 23,
    R8G8B8Snorm = 24,
    R8G8B8Uscaled = 25,
    R8G8B8Sscaled = 26,
    R8G8B8Uint = 27,
    R8G8B8Sint = 28,
    R8G8B8Srgb = 29,
    B8G8R8Unorm = 30,
    B8G8R8Snorm = 31,
    B8G8R8Uscaled = 32,
    B8G8R8Sscaled = 33,
    B8G8R8Uint = 34,
    B8G8R8Sint = 35,
    B8G8R8Srgb = 36,
    R8G8B8A8Unorm = 37,
    R8G8B8A8Snorm = 38,
    R8G8B8A8Uscaled = 39,
    R8G8B8A8Sscaled = 40,
    R8G8B8A8Uint = 41,
    R8G8B8A8Sint = 42,
    R8G8B8A8Srgb = 43,
    B8G8R8A8Unorm = 44,
    B8G8R8A8Snorm = 45,
    B8G8R8A8Uscaled = 46,
    B8G8R8A8Sscaled = 47,
    B8G8R8A8Uint = 48,
    B8G8R8A8Sint = 49,
    B8G8R8A8Srgb = 50,
    A8B8G8R8UnormPack32 = 51,
    A8B8G8R8SnormPack32 = 52,
    A8B8G8R8UscaledPack32 = 53,
    A8B8G8R8SscaledPack32 = 54,
    A8B8G8R8UintPack32 = 55,
    A8B8G8R8SintPack32 = 56,
    A8B8G8R8SrgbPack32 = 57,
    A2R10G10B10UnormPack32 = 58,
    A2R10G10B10SnormPack32 = 59,
    A2R10G10B10UscaledPack32 = 60,
    A2R10G10B10SscaledPack32 = 61,
    A2R10G10B10UintPack32 = 62,
    A2R10G10B10SintPack32 = 63,
    A2B10G10R10UnormPack32 = 64,
    A2B10G10R10SnormPack32 = 65,
    A2B10G10R10UscaledPack32 = 66,
    A2B10G10R10SscaledPack32 = 67,
    A2B10G10R10UintPack32 = 68,
    A2B10G10R10SintPack32 = 69,
    R16Unorm = 70,
    R16Snorm = 71,
    R16Uscaled = 72,
    R16Sscaled = 73,
    R16Uint = 74,
    R16Sint = 75,
    R16Sfloat = 76,
    R16G16Unorm = 77,
    R16G16Snorm = 78,
    R16G16Uscaled = 79,
    R16G16Sscaled = 80,
    R16G16Uint = 81,
    R16G16Sint = 82,
    R16G16Sfloat = 83,
    R16G16B16Unorm = 84,
    R16G16B16Snorm = 85,
    R16G16B16Uscaled = 86,
    R16G16B16Sscaled = 87,
    R16G16B16Uint = 88,
    R16G16B16Sint = 89,
    R16G16B16Sfloat = 90,
    R16G16B16A16Unorm = 91,
    R16G16B16A16Snorm = 92,
    R16G16B16A16Uscaled = 93,
    R16G16B16A16Sscaled = 94,
    R16G16B16A16Uint = 95,
    R16G16B16A16Sint = 96,
    R16G16B16A16Sfloat = 97,
    R32Uint = 98,
    R32Sint = 99,
    R32Sfloat = 100,
    R32G32Uint = 101,
    R32G32Sint = 102,
    R32G32Sfloat = 103,
    R32G32B32Uint = 104,
    R32G32B32Sint = 105,
    R32G32B32Sfloat = 106,
    R32G32B32A32Uint = 107,
    R32G32B32A32Sint = 108,
    R32G32B32A32Sfloat = 109,
    R64Uint = 110,
    R64Sint = 111,
    R64Sfloat = 112,
    R64G64Uint = 113,
    R64G64Sint = 114,
    R64G64Sfloat = 115,
    R64G64B64Uint = 116,
    R64G64B64Sint = 117,
    R64G64B64Sfloat = 118,
    R64G64B64A64Uint = 119,
    R64G64B64A64Sint = 120,
    R64G64B64A64Sfloat = 121,
    B10G11R11UfloatPack32 = 122,
    E5B9G9R9UfloatPack32 = 123,
    D16Unorm = 124,
    X8D24UnormPack32 = 125,
    D32Sfloat = 126,
    S8Uint = 127,
    D16UnormS8Uint = 128,
    D24UnormS8Uint = 129,
    D32SfloatS8Uint = 130,
    Bc1RgbUnormBlock = 131,
    Bc1RgbSrgbBlock = 132,
    Bc1RgbaUnormBlock = 133,
    Bc1RgbaSrgbBlock = 134,
    Bc2UnormBlock = 135,
    Bc2SrgbBlock = 136,
    Bc3UnormBlock = 137,
    Bc3SrgbBlock = 138,
    Bc4UnormBlock = 139,
    Bc4SnormBlock = 140,
    Bc5UnormBlock = 141,
    Bc5SnormBlock = 142,
    Bc6hUfloatBlock = 143,
    Bc6hSfloatBlock = 144,
    Bc7UnormBlock = 145,
    Bc7SrgbBlock = 146,
    Etc2R8G8B8UnormBlock = 147,
    Etc2R8G8B8SrgbBlock = 148,
    Etc2R8G8B8A1UnormBlock = 149,
    Etc2R8G8B8A1SrgbBlock = 150,
    Etc2R8G8B8A8UnormBlock = 151,
    Etc2R8G8B8A8SrgbBlock = 152,
    EacR11UnormBlock = 153,
    EacR11SnormBlock = 154,
    EacR11G11UnormBlock = 155,
    EacR11G11SnormBlock = 156,
    Astc4x4UnormBlock = 157,
    Astc4x4SrgbBlock = 158,
    Astc5x4UnormBlock = 159,
    Astc5x4SrgbBlock = 160,
    Astc5x5UnormBlock = 161,
    Astc5x5SrgbBlock = 162,
    Astc6x5UnormBlock = 163,
    Astc6x5SrgbBlock = 164,
    Astc6x6UnormBlock = 165,
    Astc6x6SrgbBlock = 166,
    Astc8x5UnormBlock = 167,
    Astc8x5SrgbBlock = 168,
    Astc8x6UnormBlock = 169,
    Astc8x6SrgbBlock = 170,
    Astc8x8UnormBlock = 171,
    Astc8x8SrgbBlock = 172,
    Astc10x5UnormBlock = 173,
    Astc10x5SrgbBlock = 174,
    Astc10x6UnormBlock = 175,
    Astc10x6SrgbBlock = 176,
    Astc10x8UnormBlock = 177,
    Astc10x8SrgbBlock = 178,
    Astc10x10UnormBlock = 179,
    Astc10x10SrgbBlock = 180,
    Astc12x10UnormBlock = 181,
    Astc12x10SrgbBlock = 182,
    Astc12x12UnormBlock = 183,
    Astc12x12SrgbBlock = 184,
  };

  enum class Filter
  {
    Nearest = 0,
    Linear = 1,
  };

  enum class CompareOp
  {
    Never = 0,
    Less = 1,
    Equal = 2,
    LessOrEqual = 3,
    Greater = 4,
    NotEqual = 5,
    GreaterOrEqual = 6,
    Always = 7,
  };

  enum class BorderColor
  {
    FloatTransparentBlack = 0,
    IntTransparentBlack = 1,
    FloatOpaqueBlack = 2,
    IntOpaqueBlack = 3,
    FloatOpaqueWhite = 4,
    IntOpaqueWhite = 5,
  };

  enum class PrimitiveTopology
  {
    PointList = 0,
    LineList = 1,
    LineStrip = 2,
    TriangleList = 3,
    TriangleStrip = 4,
    TriangleFan = 5,
    LineListWithAdjacency = 6,
    LineStripWithAdjacency = 7,
    TriangleListWithAdjacency = 8,
    TriangleStripWithAdjacency = 9,
    PatchList = 10,
  };

  enum class PolygonMode
  {
    Fill = 0,
    Line = 1,
    Point = 2,
  };

  enum class ComponentSwizzle
  {
    Identity = 0,
    Zero = 1,
    One = 2,
    R = 3,
    G = 4,
    B = 5,
    A = 6,
  };

  enum class FrontFace
  {
    CounterClockwise = 0,
    Clockwise = 1,
  };

  enum class LogicOp
  {
    Clear = 0,
    And = 1,
    AndReverse = 2,
    Copy = 3,
    AndInverted = 4,
    NoOp = 5,
    Xor = 6,
    Or = 7,
    Nor = 8,
    Equivalent = 9,
    Invert = 10,
    OrReverse = 11,
    CopyInverted = 12,
    OrInverted = 13,
    Nand = 14,
    Set = 15,
  };

  enum class BlendFactor
  {
    Zero = 0,
    One = 1,
    SrcColor = 2,
    OneMinusSrcColor = 3,
    DstColor = 4,
    OneMinusDstColor = 5,
    SrcAlpha = 6,
    OneMinusSrcAlpha = 7,
    DstAlpha = 8,
    OneMinusDstAlpha = 9,
    ConstantColor = 10,
    OneMinusConstantColor = 11,
    ConstantAlpha = 12,
    OneMinusConstantAlpha = 13,
    SrcAlphaSaturate = 14,
    Src1Color = 15,
    OneMinusSrc1Color = 16,
    Src1Alpha = 17,
    OneMinusSrc1Alpha = 18,
  };

  enum class BlendOp
  {
    Add = 0,
    Subtract = 1,
    ReverseSubtract = 2,
    Min = 3,
    Max = 4,
  };

  enum class AttachmentLoadOp
  {
    Load = 0,
    Clear = 1,
    DontCare = 2,
  };

  enum class AttachmentStoreOp
  {
    Store = 0,
    DontCare = 1,
  };

  enum class MemoryType
  {
    DeviceLocal,
    HostLocal,
    DeviceToHost,
    HostToDivice
  };

  enum class IndexType
  {
    Uint16 = 0,
    Uint32 = 1,
  };

  enum class MipMapMode
  {
    Nearest = 0,
    Linear = 1,
  };

  enum class AddressMode
  {
    Repeat = 0,
    MirroredRepeat = 1,
    ClampToEdge = 2,
    ClampToBorder = 3,
    MirrorClampToEdge = 4,
  };

  struct ComponentMapping
  {
    explicit ComponentMapping(ComponentSwizzle r = ComponentSwizzle::Identity,
        ComponentSwizzle g = ComponentSwizzle::Identity, ComponentSwizzle b = ComponentSwizzle::Identity,
        ComponentSwizzle a = ComponentSwizzle::Identity)
        : r(r), g(g), b(b), a(a)
    {
    }

    ComponentSwizzle r;
    ComponentSwizzle g;
    ComponentSwizzle b;
    ComponentSwizzle a;
  };

  struct BindingInfo
  {
    explicit BindingInfo(utils::IndexT binding = 0, utils::IndexT index = 0, utils::IndexT set = 0)
        : binding(binding), index(index), set(set)
    {
    }

    utils::IndexT binding;
    utils::IndexT index;
    utils::IndexT set;
  };

  struct DepthClearValue
  {
    explicit DepthClearValue(float depthClearValue = 1.0f, unsigned int stencilClearValue = 0)
        : depthClearValue(depthClearValue), stencilClearValue(stencilClearValue)
    {
    }

    float depthClearValue;
    unsigned stencilClearValue;
  };

  struct ColorClearValue
  {
    explicit ColorClearValue(std::array<float, 4> const& clearValue = {}) : clearValue(clearValue)
    {
    }

    std::array<float, 4> const& clearValue;
  };

  // Global -----------------------------------------------------------------------------------------------------------

  SR_MAKE_BIT_FLAGS(Extensions, {Presentation = 1u << 0u};)

  SR_MAKE_BIT_FLAGS(ValidationLayers, {StandardValidation = 1u << 0u};)

  ExtensionsFlags getSupportedExtensions();

  ValidationLayersFlags getSupportedValidationLayers();

  // PhysicalDevice ---------------------------------------------------------------------------------------------------

  enum class PhysicalDeviceType
  {
    Other = 0,
    IntegratedGpu = 1,
    DiscreteGpu = 2,
    VirtualGpu = 3,
    Cpu = 4,
  };

  class PhysicalDeviceImpl;

  class PhysicalDevice
  {
   public:
    explicit PhysicalDevice(std::shared_ptr<PhysicalDeviceImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<PhysicalDeviceImpl> const& getImpl() const
    {
      return pimpl_;
    }

    [[nodiscard]] std::string name() const noexcept;

    [[nodiscard]] PhysicalDeviceType type() const noexcept;

   private:
    std::shared_ptr<PhysicalDeviceImpl> pimpl_;
  };

  // Application ------------------------------------------------------------------------------------------------------

  SR_MAKE_BIT_FLAGS(ApplicationCreate, {};)

  struct ApplicationInfo
  {
    ApplicationInfo() = default;

    ApplicationInfo(std::string appName, std::shared_ptr<utils::Version> appVersion, std::string engineName,
        std::shared_ptr<utils::Version> engineVersion)
        : appName(std::move(appName)),
          appVersion(std::move(appVersion)),
          engineName(std::move(engineName)),
          engineVersion(std::move(engineVersion))
    {
    }

    std::string appName = "Unknown";
    std::shared_ptr<utils::Version> appVersion = std::make_shared<utils::VersionList>(0u, 0u, 0u);
    std::string engineName = "Unknown";
    std::shared_ptr<utils::Version> engineVersion = std::make_shared<utils::VersionList>(0u, 0u, 0u);
  };

  class ApplicationImpl;

  class Application
  {
   public:
    explicit Application(std::shared_ptr<ApplicationImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<ApplicationImpl> const& getImpl() const
    {
      return pimpl_;
    }

    explicit Application(ApplicationCreateFlags const& createFlags, ApplicationInfo const& appInfo,
        ExtensionsFlags const& extensions = {}, ValidationLayersFlags const& layers = {},
        utils::debug::Messenger const& messenger = {});

    [[nodiscard]] std::vector<PhysicalDevice> getSupportedPhysicalDevices() const;

   private:
    std::shared_ptr<ApplicationImpl> pimpl_;
  };

  // Device -----------------------------------------------------------------------------------------------------------

  SR_MAKE_BIT_FLAGS(DeviceCreate, {};)

  class DeviceImpl;

  class Device
  {
   public:
    explicit Device(std::shared_ptr<DeviceImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<DeviceImpl> const& getImpl() const
    {
      return pimpl_;
    }

    explicit Device(
        Application const& application, DeviceCreateFlags const& createFlags, PhysicalDevice const& physicalDevice);

   private:
    std::shared_ptr<DeviceImpl> pimpl_;
  };

  // Sampler ----------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(SamplerCreate, {};)

  // clang-format on

  class SamplerImpl;

  class Sampler
  {
   public:
    explicit Sampler(std::shared_ptr<SamplerImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<SamplerImpl> const& getImpl() const
    {
      return pimpl_;
    }

    explicit Sampler(Device const& device, SamplerCreateFlags const& createFlags = {});

    void setMagFilter(Filter const& val) noexcept;

    void setMinFilter(Filter const& val) noexcept;

    void setMipMapMode(MipMapMode const& val) noexcept;

    void setAddressModeU(AddressMode const& val) noexcept;

    void setAddressModeV(AddressMode const& val) noexcept;

    void setAddressModeW(AddressMode const& val) noexcept;

    void setMipLodBias(float val) noexcept;

    void setAnisotropy(std::optional<float> val) noexcept;

    void setCompareOp(std::optional<CompareOp> val) noexcept;

    void setMinLod(float val) noexcept;

    void setMaxLod(float val) noexcept;

    void setBorderColor(BorderColor val) noexcept;

    void setUnnormalizedCoordinates(bool val) noexcept;

    [[nodiscard]] Filter getMagFilter() const noexcept;

    [[nodiscard]] Filter getMinFilter() const noexcept;

    [[nodiscard]] MipMapMode getMipMapMode() const noexcept;

    [[nodiscard]] AddressMode getAddressModeU() const noexcept;

    [[nodiscard]] AddressMode getAddressModeV() const noexcept;

    [[nodiscard]] AddressMode getAddressModeW() const noexcept;

    [[nodiscard]] float getMipLodBias() const noexcept;

    [[nodiscard]] std::optional<float> getAnisotropy() const noexcept;

    [[nodiscard]] std::optional<CompareOp> getCompareOp() const noexcept;

    [[nodiscard]] float getMinLod() const noexcept;

    [[nodiscard]] float getMaxLod() const noexcept;

    [[nodiscard]] BorderColor getBorderColor() const noexcept;

    [[nodiscard]] bool getUnnormalizedCoordinates() const noexcept;

   private:
    std::shared_ptr<SamplerImpl> pimpl_;
  };

  // Image ------------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(ImageCreate, {};)

  SR_MAKE_BIT_FLAGS(ImageUsage, {
    TransferSrc = 0x00000001,
    TransferDst = 0x00000002,
    Sampled = 0x00000004,
    Storage = 0x00000008,
    ColorAttachment = 0x00000010,
    DepthStencilAttachment = 0x00000020,
    TransientAttachment = 0x00000040,
    InputAttachment = 0x00000080,
  };)

  // clang-format on

  struct ImageSubResourceRange
  {
    explicit ImageSubResourceRange(utils::IndexT baseMipLevel = 0, utils::SizeT mipLevelCount = 1,
        utils::IndexT baseArrayLayer = 0, utils::SizeT arrayLayerCount = 1)
        : baseMipLevel(baseMipLevel),
          mipLevelCount(mipLevelCount),
          baseArrayLayer(baseArrayLayer),
          arrayLayerCount(arrayLayerCount)
    {
    }

    utils::IndexT baseMipLevel;
    utils::SizeT mipLevelCount;
    utils::IndexT baseArrayLayer;
    utils::SizeT arrayLayerCount;
  };

  class ImageImpl;

  class Image
  {
   public:
    explicit Image(std::shared_ptr<ImageImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<ImageImpl> const& getImpl() const
    {
      return pimpl_;
    }

    explicit Image(Device const& device, ImageCreateFlags const& createFlags, utils::Extent3D const& extent,
        Format format, ImageUsageFlags const& usage, utils::SizeT mipLevelsCount = 1, utils::SizeT arrayLayersCount = 1,
        SampleCountFlagBits sampleCount = SampleCountFlagBits::e1, MemoryType memoryType = MemoryType::DeviceLocal);

    explicit Image(Device const& device, Image const& image, ImageSubResourceRange const& range,
        std::optional<Format> const& formatView, ComponentMapping const& components);

    [[nodiscard]] Format getFormat() const noexcept;

    [[nodiscard]] utils::Extent3D getExtent() const noexcept;

    [[nodiscard]] ImageSubResourceRange getSubResourceRange() const noexcept;

    [[nodiscard]] SampleCountFlagBits getSampleCount() const noexcept;

   private:
    std::shared_ptr<ImageImpl> pimpl_;
  };

  // Buffer -----------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(BufferCreate, {};)

  SR_MAKE_BIT_FLAGS(BufferUsage, {
    TransferSrc = 0x00000001,
    TransferDst = 0x00000002,
    UniformTexelBuffer = 0x00000004,
    StorageTexelBuffer = 0x00000008,
    UniformBuffer = 0x00000010,
    StorageBuffer = 0x00000020,
    IndexBuffer = 0x00000040,
    VertexBuffer = 0x00000080,
    IndirectBuffer = 0x00000100,
  };)

  class BufferMappedDataImpl;

  class BufferMappedData
  {
   public:
    explicit BufferMappedData(std::shared_ptr<BufferMappedDataImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<BufferMappedDataImpl> const& getImpl() const
    {
      return pimpl_;
    }

    [[nodiscard]] void *pData() noexcept;

    [[nodiscard]] void const* pData() const noexcept;

    void unmap();

    template<typename T>
    T* pT() noexcept
    {
      return reinterpret_cast<T*>(pData());
    }

    template<typename T>
    T const* pT() const noexcept
    {
      return reinterpret_cast<T const*>(pData());
    }

   private:
    std::shared_ptr<BufferMappedDataImpl> pimpl_;
  };

  // clang-format on

  class BufferImpl;

  class Buffer
  {
   public:
    explicit Buffer(std::shared_ptr<BufferImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<BufferImpl> const& getImpl() const
    {
      return pimpl_;
    }

    explicit Buffer(Device const& device, BufferCreateFlags const& createFlags, BufferUsageFlags const& usage,
        utils::SizeT size, MemoryType memoryType = MemoryType::DeviceLocal);

    [[nodiscard]] utils::SizeT getSize() const noexcept;

    [[nodiscard]] BufferMappedData mapMemory(utils::SizeT size, utils::OffsetT offset = 0);

   private:
    std::shared_ptr<BufferImpl> pimpl_;
  };

  // Shader -----------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(ShaderCreate, {};)

  // clang-format on

  enum class ShaderType
  {
    Vertex = 0x00000001,
    TessellationControl = 0x00000002,
    TessellationEvaluation = 0x00000004,
    Geometry = 0x00000008,
    Fragment = 0x00000010,
  };

  class ShaderImpl;

  class Shader
  {
   public:
    explicit Shader(std::shared_ptr<ShaderImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<ShaderImpl> const& getImpl() const
    {
      return pimpl_;
    }

    explicit Shader(Device const& device, ShaderCreateFlags const& createFlags = {});

    void load(ShaderType type, std::filesystem::path const& path);

    void load(ShaderType type, std::vector<std::string> const& code);
    friend bool operator<(Shader const& lhs, Shader const& rhs)
    {
      return lhs.pimpl_ < rhs.pimpl_;
    }
    friend bool operator>(Shader const& lhs, Shader const& rhs)
    {
      return rhs < lhs;
    }
    friend bool operator<=(Shader const& lhs, Shader const& rhs)
    {
      return !(rhs < lhs);
    }
    friend bool operator>=(Shader const& lhs, Shader const& rhs)
    {
      return !(lhs < rhs);
    }

   private:
    std::shared_ptr<ShaderImpl> pimpl_;
  };

  // ShaderState ------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(ShaderStateCreate, {};)

  // clang-format on

  class ShaderStateImpl;

  class ShaderState
  {
   public:
    explicit ShaderState(std::shared_ptr<ShaderStateImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<ShaderStateImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit ShaderState(Device const& device, ShaderStateCreateFlags const& createFlags = {});

    void addShader(Shader const& shader);

    void removeShader(Shader const& shader);

    void setEntryPoint(Shader const& shader, std::string const& name);

    [[nodiscard]] std::string getEntryPoint(Shader const& shader) const;

   private:
    std::shared_ptr<ShaderStateImpl> pimpl_;
  };

  // VertexInputState -------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(VertexInputStateCreate, {};)

  // clang-format on

  enum class VertexInputRate
  {
    Vertex = 0,
    Instance = 1,
  };

  class VertexInputStateImpl;

  class VertexInputState
  {
   public:
    explicit VertexInputState(std::shared_ptr<VertexInputStateImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<VertexInputStateImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit VertexInputState(Device const& device, VertexInputStateCreateFlags const& createFlags = {});

    void addInputBinding(VertexInputRate rate);

    void addInputBinding(utils::SizeT stride, VertexInputRate rate);

    void addInputAttribute(Format format);

    void addInputAttribute(Format format, utils::OffsetT offset);

    void addInputAttribute(utils::IndexT binding, Format format, utils::OffsetT offset);

    void setInputBinding(utils::IndexT binding, utils::SizeT stride, VertexInputRate rate);

    void setInputAttribute(utils::IndexT binding, utils::IndexT location, Format format, utils::OffsetT offset);

    void removeInputBinding(utils::IndexT binding);

    void removeInputAttribute(utils::IndexT binding, utils::IndexT location);

   private:
    std::shared_ptr<VertexInputStateImpl> pimpl_;
  };

  // InputAssemblyState -----------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(InputAssemblyStateCreate, {};)

  // clang-format on

  class InputAssemblyStateImpl;

  class InputAssemblyState
  {
   public:
    explicit InputAssemblyState(std::shared_ptr<InputAssemblyStateImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<InputAssemblyStateImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit InputAssemblyState(Device const& device, InputAssemblyStateCreateFlags const& createFlags = {});

    void setPrimitiveTopology(PrimitiveTopology topology) noexcept;

    void setPrimitiveRestart(bool val) noexcept;

    [[nodiscard]] PrimitiveTopology getPrimitiveTopology() const noexcept;

    [[nodiscard]] bool getPrimitiveRestart() const noexcept;

   private:
    std::shared_ptr<InputAssemblyStateImpl> pimpl_;
  };

  // RasterizationState -----------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(RasterizationStateCreate, {};)

  // clang-format on

  class RasterizationStateImpl;

  class RasterizationState
  {
   public:
    explicit RasterizationState(std::shared_ptr<RasterizationStateImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<RasterizationStateImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit RasterizationState(Device const& device, RasterizationStateCreateFlags const& createFlags = {});

    void setDepthClamp(bool val) noexcept;

    void setRasterizerDiscard(bool val) noexcept;

    void setDepthBias(bool val) noexcept;

    void setPolygonMode(PolygonMode mode) noexcept;

    void setCullMode(CullModeFlags const& cullMode) noexcept;

    void setFrontFace(FrontFace frontFace) noexcept;

    [[nodiscard]] bool getDepthClamp() const noexcept;

    [[nodiscard]] bool getRasterizerDiscard() const noexcept;

    [[nodiscard]] bool getDepthBias() const noexcept;

    [[nodiscard]] PolygonMode getPolygonMode() const noexcept;

    [[nodiscard]] CullModeFlags getCullMode() const noexcept;

    [[nodiscard]] FrontFace getFrontFace() const noexcept;

   private:
    std::shared_ptr<RasterizationStateImpl> pimpl_;
  };

  // MultisampleState -------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(MultisampleStateCreate, {};)

  // clang-format on

  class MultisampleStateImpl;

  class MultisampleState
  {
   public:
    explicit MultisampleState(std::shared_ptr<MultisampleStateImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<MultisampleStateImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit MultisampleState(Device const& device, MultisampleStateCreateFlags const& createFlags = {});

    void setRasterizationSamples(SampleCountFlagBits val) noexcept;

    void setSampleShading(std::optional<float> val) noexcept;

    void setSampleMask(uint32_t val) noexcept;

    void setAlphaToCoverage(bool val) noexcept;

    void setAlphaToOne(bool val) noexcept;

    [[nodiscard]] SampleCountFlagBits getRasterizationSamples() const noexcept;

    [[nodiscard]] std::optional<float> getSampleShading() const noexcept;

    [[nodiscard]] uint32_t getSampleMask() const noexcept;

    [[nodiscard]] bool getAlphaToCoverage() const noexcept;

    [[nodiscard]] bool getAlphaToOne() const noexcept;

   private:
    std::shared_ptr<MultisampleStateImpl> pimpl_;
  };

  // DepthStencilState ------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(DepthStencilStateCreate, {};)

  // clang-format on

  enum class StencilOp
  {
    Keep = 0,
    Zero = 1,
    Replace = 2,
    IncrementAndClamp = 3,
    DecrementAndClamp = 4,
    Invert = 5,
    IncrementAndWrap = 6,
    DecrementAndWrap = 7,
  };

  struct StencilOpInfo
  {
    explicit StencilOpInfo(
        StencilOp failOp = {}, StencilOp passOp = {}, StencilOp depthFailOp = {}, CompareOp compareOp = {})
        : failOp(failOp), passOp(passOp), depthFailOp(depthFailOp), compareOp(compareOp)
    {
    }

    StencilOp failOp;
    StencilOp passOp;
    StencilOp depthFailOp;
    CompareOp compareOp;
  };

  class DepthStencilStateImpl;

  class DepthStencilState
  {
   public:
    explicit DepthStencilState(std::shared_ptr<DepthStencilStateImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<DepthStencilStateImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit DepthStencilState(Device const& device, DepthStencilStateCreateFlags const& createFlags = {});

    void setDepthTest(bool val) noexcept;

    void setDepthWrite(bool val) noexcept;

    void setDepthCompareOp(CompareOp op) noexcept;

    void setDepthBoundsTest(bool val) noexcept;

    void setBackStencilOp(StencilOpInfo const& state) noexcept;

    void setFrontStencilOp(StencilOpInfo const& state) noexcept;

    [[nodiscard]] bool getDepthTest() const noexcept;

    [[nodiscard]] bool getDepthWrite() const noexcept;

    [[nodiscard]] CompareOp getDepthCompareOp() const noexcept;

    [[nodiscard]] bool getDepthBoundsTest() const noexcept;

    [[nodiscard]] StencilOpInfo getBackStencilOp() const noexcept;

    [[nodiscard]] StencilOpInfo getFrontStencilOp() const noexcept;

   private:
    std::shared_ptr<DepthStencilStateImpl> pimpl_;
  };

  // RenderPass -------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(RenderPassCreate, {};)

  // clang-format on

  class RenderPassImpl;

  class RenderPass
  {
   public:
    explicit RenderPass(std::shared_ptr<RenderPassImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<RenderPassImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit RenderPass(Device const& device, RenderPassCreateFlags const& createFlags = {});

    void addAttachment(std::variant<ColorClearValue, DepthClearValue> const& clearValue,
        AttachmentLoadOp loadOp = AttachmentLoadOp::Clear, AttachmentStoreOp store = AttachmentStoreOp::Store);

    void setAttachment(utils::IndexT index, std::variant<ColorClearValue, DepthClearValue> const& clearValue,
        AttachmentLoadOp loadOp = AttachmentLoadOp::Clear, AttachmentStoreOp store = AttachmentStoreOp::Store);

    void removeAttachment(utils::IndexT index);

   private:
    std::shared_ptr<RenderPassImpl> pimpl_;
  };

  // ColorBlendState --------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(ColorBlendStateCreate, {};)

  // clang-format on

  struct ColorBlendAttachment
  {
    explicit ColorBlendAttachment(BlendFactor srcColorBlendFactor = BlendFactor::One,
        BlendFactor dstColorBlendFactor = BlendFactor::Zero, BlendOp colorBlendOp = BlendOp::Add,
        BlendFactor srcAlphaBlendFactor = BlendFactor::One, BlendFactor dstAlphaBlendFactor = BlendFactor::Zero,
        BlendOp alphaBlendOp = BlendOp::Add)
        : srcColorBlendFactor(srcColorBlendFactor),
          dstColorBlendFactor(dstColorBlendFactor),
          colorBlendOp(colorBlendOp),
          srcAlphaBlendFactor(srcAlphaBlendFactor),
          dstAlphaBlendFactor(dstAlphaBlendFactor),
          alphaBlendOp(alphaBlendOp)
    {
    }

    BlendFactor srcColorBlendFactor;
    BlendFactor dstColorBlendFactor;
    BlendOp colorBlendOp;
    BlendFactor srcAlphaBlendFactor;
    BlendFactor dstAlphaBlendFactor;
    BlendOp alphaBlendOp;
  };

  class ColorBlendStateImpl;

  class ColorBlendState
  {
   public:
    explicit ColorBlendState(std::shared_ptr<ColorBlendStateImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<ColorBlendStateImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit ColorBlendState(Device const& device, ColorBlendStateCreateFlags const& createFlags = {});

    void addAttachment(std::optional<ColorBlendAttachment> const& attachment,
        ColorComponentFlags colorWriteMask = ColorComponentFlagBits::R | ColorComponentFlagBits::G |
                                             ColorComponentFlagBits::B | ColorComponentFlagBits::A);

    void setAttachment(utils::IndexT index, std::optional<ColorBlendAttachment> const& attachment,
        ColorComponentFlags colorWriteMask = ColorComponentFlagBits::R | ColorComponentFlagBits::G |
                                             ColorComponentFlagBits::B | ColorComponentFlagBits::A);

    void removeAttachment(utils::IndexT index);

    void setLogicOp(std::optional<LogicOp> val) noexcept;

    [[nodiscard]] std::optional<LogicOp> getLogicOp() const noexcept;

   private:
    std::shared_ptr<ColorBlendStateImpl> pimpl_;
  };

  // Framebuffer ------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(FramebufferCreate, {};)

  // clang-format on

  class FramebufferImpl;

  class Framebuffer
  {
   public:
    explicit Framebuffer(std::shared_ptr<FramebufferImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<FramebufferImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit Framebuffer(Device const& device, FramebufferCreateFlags const& createFlags = {});

    void addAttachment(Image const& image);

    void setAttachment(utils::IndexT index, Image const& image);

    void removeAttachment(utils::IndexT index);

   private:
    std::shared_ptr<FramebufferImpl> pimpl_;
  };

  // Viewport ---------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(ViewportCreate, {};)

  // clang-format on

  class ViewportImpl;

  class Viewport
  {
   public:
    explicit Viewport(std::shared_ptr<ViewportImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<ViewportImpl> const& getImpl() const
    {
      return pimpl_;
    }

    explicit Viewport(Device const& device, ViewportCreateFlags const& createFlags = {});

    void setExtent(utils::Extent2Df const& val) noexcept;

    void setPosition(utils::Position2Df const& val) noexcept;

    void setMinDepth(float val) noexcept;

    void setMaxDepth(float val) noexcept;

    void setViewport(utils::Viewport const& val) noexcept;

    [[nodiscard]] utils::Extent2Df getExtent() const noexcept;

    [[nodiscard]] utils::Position2Df getPosition() const noexcept;

    [[nodiscard]] float getMinDepth() const noexcept;

    [[nodiscard]] float getMaxDepth() const noexcept;

    [[nodiscard]] utils::Viewport getViewport() const noexcept;

    friend bool operator<(Viewport const& lhs, Viewport const& rhs)
    {
      return lhs.pimpl_ < rhs.pimpl_;
    }
    friend bool operator>(Viewport const& lhs, Viewport const& rhs)
    {
      return rhs < lhs;
    }
    friend bool operator<=(Viewport const& lhs, Viewport const& rhs)
    {
      return !(rhs < lhs);
    }
    friend bool operator>=(Viewport const& lhs, Viewport const& rhs)
    {
      return !(lhs < rhs);
    }

   private:
    std::shared_ptr<ViewportImpl> pimpl_;
  };

  // ViewportState ----------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(ViewportStateCreate, {};)

  // clang-format on

  class ViewportStateImpl;

  class ViewportState
  {
   public:
    explicit ViewportState(std::shared_ptr<ViewportStateImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<ViewportStateImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit ViewportState(Device const& device, ViewportStateCreateFlags const& createFlags = {});

    void addViewport(Viewport const& viewport);

    void removeViewport(Viewport const& viewport);

    void setScissor(Viewport const& viewport, utils::Rect2D const& scissor) noexcept;

    [[nodiscard]] utils::Rect2D getScissor(Viewport const& viewport) noexcept;

   private:
    std::shared_ptr<ViewportStateImpl> pimpl_;
  };

  // CommandBuffer ----------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(CommandBufferCreate, {};)

  SR_MAKE_BIT_FLAGS(CommandBufferBegin, {
    OneTimeSubmit = 0x00000001,
    SimultaneousUse = 0x00000004
  };)

  // clang-format on

  enum class CommandBufferType
  {
    Transfer,
    Graphic,
    Compute
  };

  class SemaphoreImpl;

  class Semaphore
  {
   public:
    explicit Semaphore(std::shared_ptr<SemaphoreImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<SemaphoreImpl> getImpl() const
    {
      return pimpl_;
    }

   private:
    std::shared_ptr<SemaphoreImpl> pimpl_;
  };

  struct WaitInfo
  {
    WaitInfo(Semaphore semaphore, WaitStageFlags const& waitStages)
        : semaphore(std::move(semaphore)), waitStages(waitStages)
    {
    }

    Semaphore semaphore;
    WaitStageFlags waitStages;
  };

  class CommandBufferImpl;

  class CommandBuffer
  {
   public:
    explicit CommandBuffer(std::shared_ptr<CommandBufferImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<CommandBufferImpl> const& getImpl() const
    {
      return pimpl_;
    }

    explicit CommandBuffer(Device const& device, CommandBufferCreateFlags const& createFlags, CommandBufferType type);

    Semaphore submit(std::vector<WaitInfo> const& waitInfos = {});

    void begin(CommandBufferBeginFlags const& beginFlags);

    void beginRender(Framebuffer const& framebuffer, RenderPass const& renderPass);

    // Graphic commands

    void setShaderState(ShaderState const& state);

    void setVertexInputState(VertexInputState const& state);

    void setInputAssemblyState(InputAssemblyState const& state);

    void setRasterizationState(RasterizationState const& state);

    void setMultisampleState(MultisampleState const& state);

    void setDepthStencilState(DepthStencilState const& state);

    void setViewportState(ViewportState const& state);

    void setColorBlendState(ColorBlendState const& state);

    void draw(utils::IndexT firstVertex, utils::SizeT vertexCount, utils::IndexT firstInstance = 0,
        utils::SizeT instanceCount = 1);

    void drawIndexed(utils::IndexT firstIndex, utils::SizeT indexCount, utils::IndexT firstInstance = 0,
        utils::SizeT instanceCount = 1, utils::OffsetT vertexOffset = 0);

    void bindBuffer(Buffer const& buffer, BindingInfo const& bindingInfo);

    void bindImage(Image const& image, Sampler const& sampler, BindingInfo const& bindingInfo);

    void bindVertexBuffer(Buffer const& buffer);

    void bindIndexBuffer(Buffer const& buffer, IndexType indexType);

    // Transfer commands

    void copyBuffer(Buffer const& srcBuffer, utils::OffsetT srcOffset, Buffer const& dstBuffer,
        utils::OffsetT dstOffset, utils::SizeT size);

    void copyBuffer(Buffer const& srcBuffer, Buffer const& dstBuffer);

    void copyImage(Image const& srcImage, utils::Offset3D const& srcOffset, ImageSubResourceRange const& srcSubResource,
        Image const& dstImage, utils::Offset3D const& dstOffset, ImageSubResourceRange const& dstSubResource,
        utils::Extent3D const& extent);

    void copyImage(Image const& srcImage, utils::Offset3D const& srcOffset, Image const& dstImage,
        utils::Offset3D const& dstOffset, utils::Extent3D const& extent);

    void copyImage(Image const& srcImage, Image const& dstImage);

    void copyBufferToImage(Buffer const& buffer, utils::OffsetT bufferOffset, utils::SizeT bufferRowLength,
        utils::SizeT bufferImageHeight, Image const& image, ImageSubResourceRange const& imageSubResource,
        utils::Offset3D const& imageOffset, utils::Extent3D const& imageExtent);

    void copyBufferToImage(Buffer const& buffer, utils::OffsetT bufferOffset, Image const& image,
        utils::Offset3D const& imageOffset, utils::Extent3D const& imageExtent);

    void copyBufferToImage(Buffer const& buffer, Image const& image);

   private:
    std::shared_ptr<CommandBufferImpl> pimpl_;
  };

  std::vector<CommandBuffer> createCommandBuffers(
      Device const& device, utils::SizeT count, CommandBufferCreateFlags const& createFlags, CommandBufferType type);

  std::vector<Semaphore> submitCommandBuffers(
      Device const& device, std::vector<std::pair<CommandBuffer, std::vector<WaitInfo>>> const& submitInfos);

}  // namespace vulkan