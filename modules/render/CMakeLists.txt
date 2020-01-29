project(render)

add_library(${PROJECT_NAME}
        source/core/Render/Render.cpp
        source/core/Mesh/Mesh.cpp
        source/core/Material/Material.cpp
        source/core/utils.cpp
        source/core/Texture/Texture.cpp
        source/core/Object/Object.cpp
        source/core/Camera/Camera.cpp
        source/core/Light/Light.cpp
        source/core/Collection/Collection.cpp
        source/core/Scene/Scene.cpp
        source/core/MaterialData/MaterialData.cpp
        source/core/Gui/Gui.cpp
        source/core/Presenter/Presenter.cpp)

target_include_directories(${PROJECT_NAME}
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ../../libs/stb
        )

target_compile_features(${PROJECT_NAME}
        PUBLIC
        cxx_std_17)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif ()

# libs

target_link_libraries(${PROJECT_NAME} PUBLIC utils vulkan glm imgui assimp)
