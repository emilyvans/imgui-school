cmake_minimum_required(VERSION 3.29.3)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -g")
#set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O3")
 
option(USE_GL "Use OpenGL regardless of platform" OFF)

message(${USE_GL})

project(dearimgui)

find_package(OpenGL REQUIRED)

add_definitions(-DGL_SILENCE_DEPRECATION)

add_subdirectory(./vendor/glfw-3.5.1)
add_subdirectory(./vendor/mariadb-connector-cpp-1.1.8)

add_executable(imguiapp)

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
    mariadbcpp-static)

if (APPLE AND NOT USE_GL)
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
    set(LIB_PLATFORM OpenGL::GL)
    set(SRC_PLATFORM
        ./src/renderer/GLRenderer.cpp
        ./src/GLTexture.cpp
        ./src/GLTextureLoader.cpp
        ./vendor/dearimgui/backends/imgui_impl_opengl3.cpp
    )

    target_compile_definitions(imguiapp PRIVATE USE_GL)
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
target_compile_options(imguiapp PRIVATE -Wall -g)
target_link_libraries(imguiapp PRIVATE ${LIB} ${LIB_PLATFORM})

