cmake_minimum_required(VERSION 3.29.3)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(dearimgui)

set(IMGUI_SOURCES
	./vendor/dearimgui/imgui.cpp
	./vendor/dearimgui/imgui_demo.cpp
	./vendor/dearimgui/imgui_tables.cpp
	./vendor/dearimgui/imgui_widgets.cpp
	./vendor/dearimgui/imgui_draw.cpp
	./vendor/dearimgui/backends/imgui_impl_glfw.cpp
	./vendor/dearimgui/backends/imgui_impl_opengl3.cpp
)

set(SOURCES
	./src/main.cpp
	./src/app.cpp
)


add_subdirectory(./vendor/glfw-3.5.1)

add_executable(dearimgui ${SOURCES} ${IMGUI_SOURCES})

target_link_libraries(dearimgui glfw OpenGL)

target_include_directories(dearimgui PRIVATE ./vendor/dearimgui/)
target_include_directories(dearimgui PRIVATE ./vendor/dearimgui/backends/)
