cmake_minimum_required(VERSION 3.29.3)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(dearimgui)
include(FetchContent)

set(IMGUI_SOURCES
	./vendor/dearimgui/imgui.cpp
	./vendor/dearimgui/imgui_demo.cpp
	./vendor/dearimgui/imgui_tables.cpp
	./vendor/dearimgui/imgui_widgets.cpp
	./vendor/dearimgui/imgui_draw.cpp
	./vendor/dearimgui/backends/imgui_impl_glfw.cpp
	./vendor/dearimgui/backends/imgui_impl_opengl3.cpp
	./vendor/dearimgui/misc/cpp/imgui_stdlib.cpp
)

set(SOURCES
	./src/main.cpp
	./src/app.cpp
)

FetchContent_Declare(glfw
	SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/vendor/glfw-3.5.1/"
)

set(CONC_WITH_UNIT_TESTS Off)
FetchContent_Declare(mariadbcpp
	SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/vendor/mariadb-connector-cpp-1.1.8/"
)

FetchContent_MakeAvailable(glfw mariadbcpp)

find_package(OpenGL REQUIRED)


add_executable(dearimgui ${SOURCES} ${IMGUI_SOURCES})

target_link_libraries(dearimgui glfw OpenGL::GL mariadbcpp-static)

target_include_directories(dearimgui PRIVATE ./vendor/dearimgui/)
target_include_directories(dearimgui PRIVATE ./vendor/dearimgui/backends/)
