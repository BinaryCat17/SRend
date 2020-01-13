#pragma once
#include <utils/debug.hpp>
#include <utils/utils.hpp>

namespace vulkan
{
  // Enums ------------------------------------------------------------------------------------------------------------

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

  // Structs ----------------------------------------------------------------------------------------------------------

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

  // Sampler ----------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(SamplerCreate, {};)

  // clang-format on

  enum class SamplerMipMapMode
  {
    Nearest = 0,
    Linear = 1,
  };

  enum class SamplerAddressMode
  {
    Repeat = 0,
    MirroredRepeat = 1,
    ClampToEdge = 2,
    ClampToBorder = 3,
    MirrorClampToEdge = 4,
  };

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

    void setMagFilter(Filter const& val);

    void setMinFilter(Filter const& val);

    void setMipMapMode(SamplerMipMapMode const& val);

    void setAddressModeU(SamplerAddressMode const& val);

    void setAddressModeV(SamplerAddressMode const& val);

    void setAddressModeW(SamplerAddressMode const& val);

    void setMipLodBias(float val);

    void enableAnisotropy(float val);

    void disableAnisotropy();

    void enableCompareOp(CompareOp val);

    void disableCompareOp();

    void setMinLod(float val);

    void setMaxLod(float val);

    void setBorderColor(BorderColor val);

    void enableUnnormalizedCoordinates();

    void disableUnnormalizedCoordinates();

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

    [[nodiscard]] Format getFormat() const;

    [[nodiscard]] utils::Extent3D getExtent() const;

    [[nodiscard]] ImageSubResourceRange getSubResourceRange() const;

    [[nodiscard]] SampleCountFlagBits getSampleCount() const;

   private:
    std::shared_ptr<ImageImpl> pimpl_;
  };

  // Buffer -----------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(BufferCreate, {};)

  SR_MAKE_BIT_FLAGS(BufferUsage, {
    TransferSrcBit = 0x00000001,
    TransferDstBit = 0x00000002,
    UniformTexelBufferBit = 0x00000004,
    StorageTexelBufferBit = 0x00000008,
    UniformBufferBit = 0x00000010,
    StorageBufferBit = 0x00000020,
    IndexBufferBit = 0x00000040,
    VertexBufferBit = 0x00000080,
    IndirectBufferBit = 0x00000100,
  };)

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

    [[nodiscard]] utils::SizeT getSize() const;

    [[nodiscard]] void* mapMemory(utils::SizeT size, utils::OffsetT offset = 0);

    void unmapMemory();

   private:
    std::shared_ptr<BufferImpl> pimpl_;
  };

  // Shader -----------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(ShaderCreate, {};)

  // clang-format on

  enum class ShaderType
  {
    Vertex = 0x00000004,
    TessellationControl = 0x00000010,
    TessellationEvaluation = 0x00000020,
    Geometry = 0x00000040,
    Fragment = 0x00000080,
  };

  class ShaderImpl;

  class Shader
  {
   public:
    explicit Shader(std::shared_ptr<ShaderImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<ShaderImpl> getImpl() const
    {
      return pimpl_;
    }

    void load(std::filesystem::path const& path);

    void load(ShaderType type, std::vector<std::string> const& code);

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

    void addShader(Shader const& shader);

    void setShaderEntryPoint(utils::IndexT index, std::string const& name);

    void setShaderSpecConstant(utils::IndexT index, utils::IndexT constantId, utils::SharedAnyPtr const& pData);

    void removeShader(utils::IndexT index);

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

    void addInputBinding(VertexInputRate rate);

    void addInputBinding(utils::SizeT stride, VertexInputRate rate);

    void addInputAttribute(Format format);

    void addInputAttribute(Format format, utils::OffsetT offset);

    void addInputAttribute(utils::IndexT binding, Format format, utils::OffsetT offset);

    void setInputBinding(utils::IndexT binding, utils::SizeT stride, VertexInputRate rate);

    void setInputAttribute(utils::IndexT binding, utils::IndexT location, Format format, utils::OffsetT offset);

    void eraseInputBinding(utils::IndexT binding);

    void eraseInputAttribute(utils::IndexT binding, utils::IndexT location);

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

    void setPrimitiveTopology(PrimitiveTopology topology);

    void enablePrimitiveRestart();

    void disablePrimitiveRestart();

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

    void enableDepthClamp();

    void disableDepthClamp();

    void enableRasterizerDiscard();

    void disableRasterizerDiscard();

    void enableDepthBias();

    void disableDepthBias();

    void setPolygonMode(PolygonMode mode);

    void setCullMode(CullModeFlags const& cullMode);

    void setFrontFace(FrontFace frontFace);

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

    void setRasterizationSamples(SampleCountFlagBits sampleCount);

    void enableSampleShading(float minSampleShading);

    void disableSampleShading();

    void setSampleMask(uint32_t mask);

    void enableAlphaToCoverage();

    void disableAlphaToCoverage();

    void enableAlphaToOne();

    void disableAlphaToOne();

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

    void enableDepthTest();

    void disableDepthTest();

    void enableDepthWrite();

    void disableDepthWrite();

    void setDepthCompareOp(CompareOp op);

    void enableDepthBoundsTest();

    void disableDepthBoundsTest();

    void setBackStencilOp(StencilOpInfo const& state);

    void setFrontStencilOp(StencilOpInfo const& state);

   private:
    std::shared_ptr<DepthStencilStateImpl> pimpl_;
  };

  // ColorBlendState --------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(ColorBlendStateCreate, {};)

  // clang-format on

  struct ColorBlendAttachmentInfo
  {
    ColorBlendAttachmentInfo(BlendFactor srcColorBlendFactor = BlendFactor::One,
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

    void addColorBlendAttachment(std::optional<ColorBlendAttachmentInfo> const& info,
        ColorComponentFlags colorWriteMask = ColorComponentFlagBits::R | ColorComponentFlagBits::G |
                                             ColorComponentFlagBits::B | ColorComponentFlagBits::A);

    void setColorBlendAttachment(utils::IndexT index, std::optional<ColorBlendAttachmentInfo> const& info,
        ColorComponentFlags colorWriteMask = ColorComponentFlagBits::R | ColorComponentFlagBits::G |
                                             ColorComponentFlagBits::B | ColorComponentFlagBits::A);

    void removeColorBlendAttachment(utils::IndexT index);

   private:
    std::shared_ptr<ColorBlendStateImpl> pimpl_;
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

    void addViewport(utils::Viewport const& viewport, utils::Rect2D const& scissor);

    void setViewport(utils::IndexT index, utils::Viewport const& viewport);

    void setScissor(utils::IndexT index, utils::Rect2D const& scissor);

    void removeViewport(utils::IndexT index);

   private:
    std::shared_ptr<ViewportStateImpl> pimpl_;
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

    void addColorAttachment(std::array<float, 4> const& clearValue = {0, 0, 0, 0},
        AttachmentLoadOp loadOp = AttachmentLoadOp::Clear, AttachmentStoreOp store = AttachmentStoreOp::Store);

    void addDepthAttachment(float depthClearValue = 1.0f, unsigned stencilClearValue = 0,
        AttachmentLoadOp loadOp = AttachmentLoadOp::Clear, AttachmentStoreOp store = AttachmentStoreOp::Store);

   private:
    std::shared_ptr<RenderPassImpl> pimpl_;
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

   private:
    std::shared_ptr<FramebufferImpl> pimpl_;
  };

  // Semaphore --------------------------------------------------------------------------------------------------------

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

  // CommandBuffer ----------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(CommandBufferCreate, {};)

  SR_MAKE_BIT_FLAGS(CommandBufferBegin, {
    OneTimeSubmit = 0x00000001,
    SimultaneousUse = 0x00000004
  };)

  // clang-format on

  struct WaitInfo
  {
    WaitInfo(Semaphore semaphore, WaitStageFlags const& waitStages)
        : semaphore(std::move(semaphore)), waitStages(waitStages)
    {
    }

    Semaphore semaphore;
    WaitStageFlags waitStages;
  };

  enum class CommandBufferType
  {
    Transfer,
    Graphic,
    Compute
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

    void begin(CommandBufferBeginFlags const& beginFlags);

    void end();

    void beginRender(Framebuffer const& framebuffer, RenderPass const& renderPass);

    void endRender();

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

    void bindImage(Image const& image, BindingInfo const& bindingInfo);

    void bindImage(Sampler const& sampler, BindingInfo const& bindingInfo);

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

    [[nodiscard]] std::vector<CommandBuffer> createCommandBuffers(
        utils::SizeT count, CommandBufferCreateFlags const& createFlags, CommandBufferType type) const;

    [[nodiscard]] CommandBuffer createCommandBuffer(
        CommandBufferCreateFlags const& createFlags, CommandBufferType type) const;

    [[nodiscard]] std::vector<Semaphore> submitCommandBuffers(
        std::vector<std::pair<CommandBuffer, std::vector<WaitInfo>>> const& submitInfos, CommandBufferType type) const;

    [[nodiscard]] Semaphore submitCommandBuffer(
        CommandBuffer const& commandBuffer, std::vector<WaitInfo> const& waitInfos, CommandBufferType type) const;

    [[nodiscard]] Buffer createBuffer(BufferCreateFlags const& createFlags, MemoryType memoryType,
        BufferUsageFlags const& usage, utils::SizeT size, utils::AlignmentT alignment = 0) const;

    [[nodiscard]] Image createImage(ImageCreateFlags const& createFlags, Format format, ImageUsageFlags const& usage,
        utils::Extent3D const& extent, utils::SizeT mipLevelsCount = 1, utils::SizeT arrayLayersCount = 1,
        SampleCountFlagBits sampleCount = SampleCountFlagBits::e1,
        MemoryType memoryType = MemoryType::DeviceLocal) const;

    [[nodiscard]] Framebuffer createFramebuffer(
        FramebufferCreateFlags const& createFlags, std::vector<Image> const& images) const;

    [[nodiscard]] Image createImage(Image const& image, ImageSubResourceRange const& range,
        std::optional<Format> const& formatView, ComponentMapping const& components = ComponentMapping{}) const;

    [[nodiscard]] Sampler createSampler(SamplerCreateFlags createFlags = {}) const;

    [[nodiscard]] Shader createShader(ShaderCreateFlags createFlags = {}) const;

    [[nodiscard]] ShaderState createShaderState(ShaderStateCreateFlags const& createFlags = {}) const;

    [[nodiscard]] VertexInputState createVertexInputState(VertexInputStateCreateFlags const& createFlags = {}) const;

    [[nodiscard]] InputAssemblyState createInputAssemblyState(
        InputAssemblyStateCreateFlags const& createFlags = {}) const;

    [[nodiscard]] RasterizationState createRasterizationState(
        RasterizationStateCreateFlags const& createFlags = {}) const;

    [[nodiscard]] MultisampleState createMultisampleState(MultisampleStateCreateFlags const& createFlags = {}) const;

    [[nodiscard]] DepthStencilState createDepthStencilState(DepthStencilStateCreateFlags const& createFlags = {}) const;

    [[nodiscard]] ColorBlendState createColorBlendState(ColorBlendStateCreateFlags const& createFlags = {}) const;

    [[nodiscard]] ViewportState createViewportState(ViewportStateCreateFlags const& createFlags = {}) const;

    [[nodiscard]] RenderPass createRenderPass(RenderPassCreateFlags const& createFlags = {}) const;

   private:
    std::shared_ptr<DeviceImpl> pimpl_;
  };

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

    [[nodiscard]] std::string name() const;

    [[nodiscard]] PhysicalDeviceType type() const;

   private:
    std::shared_ptr<PhysicalDeviceImpl> pimpl_;
  };

  // Global -----------------------------------------------------------------------------------------------------------

  SR_MAKE_BIT_FLAGS(Extensions, {Presentation = 1u << 0u};)

  SR_MAKE_BIT_FLAGS(ValidationLayers, {StandardValidation = 1u << 0u};)

  ExtensionsFlags getSupportedExtensions();

  ValidationLayersFlags getSupportedValidationLayers();

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

    [[nodiscard]] Device createDevice(DeviceCreateFlags const& createFlags, PhysicalDevice const& physicalDevice) const;

   private:
    std::shared_ptr<ApplicationImpl> pimpl_;
  };

}  // namespace vulkan