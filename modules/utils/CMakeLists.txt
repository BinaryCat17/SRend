# utils -------------------------------------------------------------------------------------------

project(utils)

add_library(${PROJECT_NAME}
        source/Allocator/Allocator.cpp
        source/Allocator/AllocatorImpl.cpp
        source/Allocator/AllocatorPolitics.cpp
        source/AnyPtr/AnyPtr.cpp
        ./source/debug/Messenger.cpp
        ./source/debug/MessengerCallbacks.cpp
        ./source/debug/Tester.cpp
        source/stringUtils/stringUtils.cpp
        source/Version/Version.cpp
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

# libs --------------------------------------------------------------------------------------------

target_link_libraries(${PROJECT_NAME} PUBLIC magic_enum)