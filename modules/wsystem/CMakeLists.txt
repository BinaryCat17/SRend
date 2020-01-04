project(wsystem)

add_library(${PROJECT_NAME}
        source/Manager/Manager.cpp
        source/Window/Window.cpp
        source/Window/WindowImpl.cpp
        source/vulkan/vulkan.cpp
        source/sdl/SDLManager.cpp
        source/sdl/SdlWindow.cpp
        source/sdl/SdlVulkan.cpp
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

target_link_libraries(${PROJECT_NAME} PUBLIC utils PRIVATE SDL2)


