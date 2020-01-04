project(vulkan)

add_library(${PROJECT_NAME}
        source/utils.cpp
        source/core/Application/Application.cpp
        source/core/Application/ApplicationImpl.cpp
        source/core/PhysicalDevice/PhysicalDevice.cpp
        source/core/PhysicalDevice/PhysicalDeviceImpl.cpp
        source/core/Device/DeviceImpl.cpp
        source/core/Device/Device.cpp
        source/core/Device/BufferManager.cpp
        source/core/CommandBuffer/CommandBuffer.cpp
        source/core/CommandBuffer/CommandBufferImpl.cpp
        source/core/Buffer/Buffer.cpp
        source/core/Buffer/BufferImpl.cpp
        source/core/Semaphore/Semaphore.cpp
        source/core/Semaphore/SemaphoreImpl.cpp
        source/core/Image/Image.cpp
        source/core/Image/ImageImpl.cpp
        source/core/Sampler/Sampler.cpp
        source/core/Sampler/SamplerImpl.cpp
        source/core/Shader/Shader.cpp
        source/core/Shader/ShaderImpl.cpp
        source/core/Pipeline/Pipeline.cpp
        source/core/Pipeline/PipelineImpl.cpp
        )

target_include_directories(${PROJECT_NAME}
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_compile_features(${PROJECT_NAME}
        PUBLIC
        cxx_std_17)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif ()

# libs

find_package(Vulkan REQUIRED FATAL_ERROR)
target_link_libraries(${PROJECT_NAME} PUBLIC utils wsystem PRIVATE VEZ Vulkan::Vulkan)

