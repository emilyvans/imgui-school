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
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <AppKit/AppKit.hpp>

#include "renderer/MetalRenderer.hpp"
#include "MetalTextureLoader.hpp"

using RendererImpl = MetalRenderer;
using WindowImpl = Window<Metal>;
#else
#include "renderer/GLRenderer.hpp"
#include "GLTextureLoader.hpp"

using RendererImpl = GLRenderer;
using WindowImpl = Window<OpenGL>;
#endif

int main(int argc, char** argv)
{
    if (!glfwInit()) return 1;

    WindowImpl window{800, 600, "test"};
    RendererImpl renderer{window};

#ifdef APPLE
    MetalTextureLoader texLoader{renderer.device()};
#else
    GLTextureLoader texLoader{};
#endif

    App app{texLoader};

    while (!window.shouldClose()) {
        renderer.render([&app]() { app.draw(); });
    }

    glfwTerminate();

    return 0;
}
