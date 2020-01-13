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

target_include_directories(VEZ
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/V-EZ/Source>
        $<INSTALL_INTERFACE:V-EZ/Source>)


