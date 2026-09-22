cmake_minimum_required(VERSION 3.29.3)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


project(dearimgui)

find_package(OpenGL REQUIRED)

add_definitions(-DGL_SILENCE_DEPRECATION)

set(IMGUI_SOURCES
	./vendor/dearimgui/imgui.cpp
	./vendor/dearimgui/imgui_demo.cpp
	./vendor/dearimgui/imgui_tables.cpp
	./vendor/dearimgui/imgui_widgets.cpp
	./vendor/dearimgui/imgui_draw.cpp
	./vendor/dearimgui/backends/imgui_impl_glfw.cpp
	./vendor/dearimgui/misc/cpp/imgui_stdlib.cpp
)

set(SOURCES
	./src/main.cpp
	./src/App.cpp
        ./src/Window.cpp
        ./src/Texture.cpp
        ./src/renderer/Renderer.cpp
)

set(LIB
    glfw
    mariadbcpp-static)

add_compile_definitions(APPLE=${APPLE})

if (APPLE)
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
else()
    set(LIB_PLATFORM OpenGL::GL)
    set(SRC_PLATFORM
        ./src/renderer/GLRenderer.cpp
        ./src/GLTexture.cpp
        ./src/GLTextureLoader.cpp
	./vendor/dearimgui/backends/imgui_impl_opengl3.cpp
    )
endif()

add_subdirectory(./vendor/glfw-3.5.1)
add_subdirectory(./vendor/mariadb-connector-cpp-1.1.8)

add_executable(dearimgui ${SOURCES} ${SRC_PLATFORM} ${IMGUI_SOURCES})

target_link_libraries(dearimgui ${LIB} ${LIB_PLATFORM})

target_include_directories(dearimgui PRIVATE
    ./vendor/metal-cpp-extensions/
    ./vendor/metal-cpp/
    ./vendor/dearimgui/
    ./vendor/dearimgui/backends/
    ./src/
)
