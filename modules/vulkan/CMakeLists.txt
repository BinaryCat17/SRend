project(vulkan)

add_library(${PROJECT_NAME}
        source/utils.cpp
        source/core/Application/Application.cpp
        source/core/PhysicalDevice/PhysicalDevice.cpp
        source/core/Device/Device.cpp
        source/core/Device/BufferManager.cpp
        source/core/CommandBuffer/CommandBuffer.cpp
        source/core/Buffer/Buffer.cpp
        source/core/Semaphore/Semaphore.cpp
        source/core/Image/Image.cpp
        source/core/Sampler/Sampler.cpp
        source/core/Shader/Shader.cpp
        source/core/ShaderState/ShaderState.cpp
        source/core/Framebuffer/Framebuffer.cpp
        source/core/VertexInputState/VertexInputState.cpp
        source/core/InputAssemblyState/InputAssemblyState.cpp
        source/core/RasterizationState/RasterizationState.cpp
        source/core/MultisampleState/MultisampleState.cpp
        source/core/DepthStencilState/DepthStencilState.cpp
        source/core/ColorBlendState/ColorBlendState.cpp
        source/core/ViewportState/ViewportState.cpp
        source/core/RenderPass/RenderPass.cpp
        source/core/Framebuffer/Framebuffer.cpp
        )

target_include_directories(${PROJECT_NAME}
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_compile_features(${PROJECT_NAME}
        PUBLIC
        cxx_std_20)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif ()

# libs

find_package(Vulkan REQUIRED FATAL_ERROR)
target_link_libraries(${PROJECT_NAME} PUBLIC utils wsystem PRIVATE VEZ Vulkan::Vulkan)

