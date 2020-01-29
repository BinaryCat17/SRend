add_subdirectory(magic_enum)
add_subdirectory(SDL-mirror)
add_subdirectory(re2)
add_subdirectory(SPIRV-Headers)
add_subdirectory(SPIRV-Tools)
add_subdirectory(V-EZ)
add_subdirectory(googletest)
add_subdirectory(shaderc)
add_subdirectory(effcee)
add_subdirectory(GSL)
add_subdirectory(glm)
add_subdirectory(assimp)

target_include_directories(VEZ
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/V-EZ/Source>
        $<INSTALL_INTERFACE:V-EZ/Source>)

add_library(imgui
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_impl_sdl.cpp
        )

target_link_libraries(imgui PUBLIC SDL2)

target_include_directories(imgui
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui>
        $<INSTALL_INTERFACE:include>)


add_library(imgui-filebrowser INTERFACE)

target_compile_features(imgui-filebrowser
        INTERFACE
        cxx_std_17)


target_link_libraries(imgui-filebrowser INTERFACE imgui)

target_include_directories(imgui-filebrowser
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<INSTALL_INTERFACE:include>)