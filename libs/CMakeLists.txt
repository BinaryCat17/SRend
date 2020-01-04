add_subdirectory(magic_enum)
add_subdirectory(SDL-mirror)
add_subdirectory(V-EZ)
add_subdirectory(shaderc)

target_include_directories(VEZ
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/V-EZ/Source>
        $<INSTALL_INTERFACE:V-EZ/Source>)