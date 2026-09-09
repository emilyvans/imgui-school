// Dear ImGui: standalone example application for GLFW + OpenGL 3, using
// programmable pipeline (GLFW is a cross-platform general purpose library for
// handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation,
// etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/
// folder).
// - Introduction, links and more at the top of imgui.cpp

#include "App.hpp"

#include "Window.hpp"

#if APPLE
#include "renderer/MetalRenderer.h"
#else
#include "renderer/GLRenderer.hpp"
#endif


int main(int argc, char** argv)
{
    if (!glfwInit()) return 1;

    Window<APPLE ? Metal : OpenGL> window{800, 600, "test"};
#if APPLE
    MetalRenderer renderer{window};
#else
    GLRenderer renderer{window};
#endif
    App app;

    while (!window.shouldClose()) {
        renderer.render([&app]() { app.draw(); });
    }

    glfwTerminate();

    return 0;
}
