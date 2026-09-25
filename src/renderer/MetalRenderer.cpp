#include "MetalRenderer.hpp"

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

#define IMGUI_IMPL_METAL_CPP
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_metal.h>

MetalRenderer::MetalRenderer(Window<Metal>& win)
    : _win{win} {
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(
        glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    // ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale); // Bake a fixed style scale. (until we have a
                                     // solution for dynamic style scaling, changing this
                                     // requires resetting Style + calling this again)
    style.FontScaleDpi =
        main_scale; // Set initial font scale. (in docking branch: using
                    // io.ConfigDpiScaleFonts=true automatically overrides this
                    // for every window depending on the current monitor)

    _device = NS::TransferPtr(MTL::CreateSystemDefaultDevice());
    _commandQueue = NS::TransferPtr(_device->newCommandQueue());

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(_win.glfwWindow(), true);
    ImGui_ImplMetal_Init(_device.get());

    // Load Fonts
    // - If fonts are not explicitly loaded, Dear ImGui will select an embedded
    // font: either AddFontDefaultVector() or AddFontDefaultBitmap().
    //   This selection is based on (style.FontSizeBase * style.FontScaleMain *
    //   style.FontScaleDpi) reaching a small threshold.
    // - You can load multiple fonts and use ImGui::PushFont()/PopFont() to
    // select them.
    // - If a file cannot be loaded, AddFont functions will return a nullptr.
    // Please handle those errors in your code (e.g. use an assertion, display
    // an error and quit).
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use
    // FreeType for higher quality font rendering.
    // - Remember that in C/C++ if you want to include a backslash \ in a string
    // literal you need to write a double backslash \\ !
    // style.FontSizeBase = 20.0f;
    // io.Fonts->AddFontDefaultVector();
    // io.Fonts->AddFontDefaultBitmap();
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf");
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf");
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf");
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf");
    // ImFont* font =
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf");
    // IM_ASSERT(font != nullptr);

    auto nswin = reinterpret_cast<NS::Window*>(glfwGetCocoaWindow(_win.glfwWindow()));

    _layer = NS::TransferPtr(CA::MetalLayer::layer());
    _layer->setDevice(_device.get());
    _layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);

    auto view = nswin->contentView();

    view->setLayer(_layer.get());
    view->setWantsLayer(true);

    _renderPassDescriptor =
        NS::TransferPtr(MTL::RenderPassDescriptor::renderPassDescriptor());
}

MetalRenderer::~MetalRenderer() {
    ImGui_ImplMetal_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool MetalRenderer::renderBegin() {
    if (_renderStarted)
        return false;
    _renderStarted = true;

    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to
    // tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to
    // your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input
    // data to your main application, or clear/overwrite your copy of the
    // keyboard data. Generally you may always pass all inputs to dear imgui,
    // and hide them from your application based on those two flags.
    glfwPollEvents();

    int width;
    int height;
    glfwGetFramebufferSize(_win.glfwWindow(), &width, &height);

    _layer->setDrawableSize(CGSizeMake(width, height));

    _curDrawable = _layer->nextDrawable();
    _curCommandBuffer = _commandQueue->commandBuffer();

    auto colorAtt0 = _renderPassDescriptor->colorAttachments()->object(0);
    //_objc->renderPassDescriptor.colorAttachments[0].clearColor =
    // MTLClearColorMake(clear_color[0] * clear_color[3], clear_color[1] *
    // clear_color[3], clear_color[2] * clear_color[3], clear_color[3]);
    colorAtt0->setTexture(_curDrawable->texture());
    colorAtt0->setLoadAction(MTL::LoadActionClear);
    colorAtt0->setStoreAction(MTL::StoreActionStore);

    _curRenderEncoder =
        _curCommandBuffer->renderCommandEncoder(_renderPassDescriptor.get());
    _curRenderEncoder->pushDebugGroup(
        NS::String::string("ImGui app", NS::StringEncoding::UTF8StringEncoding));

    // Start the Dear ImGui frame
    ImGui_ImplMetal_NewFrame(_renderPassDescriptor.get());
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    return true;
}

bool MetalRenderer::renderEnd() {
    if (!_renderStarted)
        return false;
    _renderStarted = false;

    // Rendering
    ImGui::Render();
    ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), _curCommandBuffer,
                                   _curRenderEncoder);

    _curRenderEncoder->popDebugGroup();
    _curRenderEncoder->endEncoding();

    _curCommandBuffer->presentDrawable(_curDrawable);
    _curCommandBuffer->commit();

    // release temp objects
    _curDrawable->release();
    _curCommandBuffer->release();
    _curRenderEncoder->release();

    return true;
}

NS::SharedPtr<MTL::Device> MetalRenderer::device() const {
    return _device;
}
