project(test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} utils wsystem vulkan glm assimp render imgui-filebrowser)

target_compile_features(${PROJECT_NAME}
        PUBLIC
        cxx_std_17)
