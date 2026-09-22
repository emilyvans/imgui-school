#pragma once

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include <imgui.h>

#include "TextureLoader.hpp"

class App {
private:
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    TextureLoader& _texLoader;

public:
    App(TextureLoader& texLoader);

    void draw();
};

