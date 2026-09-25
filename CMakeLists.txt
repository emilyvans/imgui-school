cmake_minimum_required(VERSION 3.29.3)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_C_COMPILER gcc-16)
#set(CMAKE_CXX_COMPILER g++-16)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")
 
option(USE_GL "Use OpenGL regardless of platform" OFF)

project(dearimgui)
include(FetchContent)
FetchContent_Declare(glfw
	SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/vendor/glfw-3.5.1/"
)

set(CONC_WITH_UNIT_TESTS Off)
FetchContent_Declare(mariadbcpp
	SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/vendor/mariadb-connector-cpp-1.1.8/"
)

FetchContent_MakeAvailable(glfw mariadbcpp)

add_executable(imguiapp)

add_custom_command(TARGET imguiapp PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

set(SRC_IMGUI
    ./vendor/dearimgui/imgui.cpp
    ./vendor/dearimgui/imgui_demo.cpp
    ./vendor/dearimgui/imgui_tables.cpp
    ./vendor/dearimgui/imgui_widgets.cpp
    ./vendor/dearimgui/imgui_draw.cpp
    ./vendor/dearimgui/backends/imgui_impl_glfw.cpp
    ./vendor/dearimgui/misc/cpp/imgui_stdlib.cpp
)
set(SRC
    ./src/main.cpp
    ./src/App.cpp
    ./src/Window.cpp
    ./src/Utils.cpp
    ./src/Texture.cpp
    ./src/TextureLoader.cpp
    ./src/TextureStore.cpp
    ./src/renderer/Renderer.cpp
)

set(LIB
    glfw
    mariadbcpp-static
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build")
    list(APPEND LIB profiler)
endif()

if (APPLE AND NOT USE_GL)
    message(STATUS "Graphics API: Metal")

    set(LIB_PLATFORM
        "-framework Foundation"
        "-framework QuartzCore"
        "-framework Metal"
        #"-framework MetalKit"
        #"-framework Cocoa"
        #"-framework IOKit"
        #"-framework CoreVideo"
    )
    set(SRC_PLATFORM
        ./src/renderer/MetalRenderer.cpp
        ./src/MetalTexture.cpp
        ./src/MetalTextureLoader.cpp
        ./vendor/dearimgui/backends/imgui_impl_metal.mm
    )

    target_compile_definitions(imguiapp PRIVATE USE_METAL)
else()
    find_package(OpenGL REQUIRED)

    message(STATUS "Graphics API: OpenGL")

    set(LIB_PLATFORM OpenGL::GL)
    set(SRC_PLATFORM
        ./src/renderer/GLRenderer.cpp
        ./src/GLTexture.cpp
        ./src/GLTextureLoader.cpp
        ./vendor/dearimgui/backends/imgui_impl_opengl3.cpp
    )

    target_compile_definitions(imguiapp PRIVATE
        USE_GL
        GL_SILENCE_DEPRECATION
    )

endif()

target_include_directories(imguiapp PRIVATE
    ./vendor/metal-cpp-extensions/
    ./vendor/metal-cpp/
    ./vendor/dearimgui/
    ./vendor/dearimgui/backends/
    ./vendor/stb/
    ./src/
)

target_sources(imguiapp PRIVATE ${SRC} ${SRC_PLATFORM} ${SRC_IMGUI})
target_compile_options(imguiapp PRIVATE -Wall)
target_link_libraries(imguiapp PRIVATE ${LIB} ${LIB_PLATFORM})

