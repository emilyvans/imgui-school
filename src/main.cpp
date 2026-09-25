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

#if defined(USE_METAL)
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

#include "MetalTextureLoader.hpp"
#include "renderer/MetalRenderer.hpp"

using RendererImpl = MetalRenderer;
using WindowImpl = Window<Metal>;
using TextureLoaderImpl = MetalTextureLoader;
#else
#include "GLTextureLoader.hpp"
#include "renderer/GLRenderer.hpp"

using RendererImpl = GLRenderer;
using WindowImpl = Window<OpenGL>;
using TextureLoaderImpl = GLTextureLoader;
#endif

int main(int argc, char** argv) {
    if (!glfwInit())
        return 1;

    WindowImpl window{800, 600, "test"};
    RendererImpl renderer{window};
    TextureLoaderImpl texLoader{};

#ifdef USE_METAL
    texLoader.setDevice(renderer.device());
#endif

    App app{texLoader};

    while (!window.shouldClose()) {
        renderer.render([&app]() { app.draw(); });
    }

    glfwTerminate();

    return 0;
}
