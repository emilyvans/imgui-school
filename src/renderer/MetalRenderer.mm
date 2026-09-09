#include "MetalRenderer.h"

#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_metal.h"

struct MetalRenderer::ObjCStorage {
    MTLRenderPassDescriptor* renderPassDescriptor;
    CAMetalLayer* layer;
    id <MTLDevice> device;
    id <MTLCommandQueue> commandQueue;

    id <MTLRenderCommandEncoder> curRenderEncoder;
    id <MTLCommandBuffer> curCommandBuffer;
    id <CAMetalDrawable> curDrawable;
};

MetalRenderer::MetalRenderer(Window<Metal>& win)
    : _objc{std::make_unique<ObjCStorage>()}, _win{win}
{
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

    _objc->device = MTLCreateSystemDefaultDevice();
    _objc->commandQueue = [_objc->device newCommandQueue];

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(_win.glfwWindow(), true);
    ImGui_ImplMetal_Init(_objc->device);

    // Load Fonts
    // - If fonts are not explicitly loaded, Dear ImGui will select an embedded font: either AddFontDefaultVector() or AddFontDefaultBitmap().
    //   This selection is based on (style.FontSizeBase * style.FontScaleMain * style.FontScaleDpi) reaching a small threshold.
    // - You can load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - If a file cannot be loaded, AddFont functions will return a nullptr. Please handle those errors in your code (e.g. use an assertion, display an error and quit).
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use FreeType for higher quality font rendering.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //style.FontSizeBase = 20.0f;
    //io.Fonts->AddFontDefaultVector();
    //io.Fonts->AddFontDefaultBitmap();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf");
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf");
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf");
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf");
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf");
    //IM_ASSERT(font != nullptr);

    NSWindow *nswin = glfwGetCocoaWindow(_win.glfwWindow());
    _objc->layer = [CAMetalLayer layer];
    _objc->layer.device = _objc->device;
    _objc->layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    nswin.contentView.layer = _objc->layer;
    nswin.contentView.wantsLayer = YES;

    _objc->renderPassDescriptor = [MTLRenderPassDescriptor new];
}

MetalRenderer::~MetalRenderer()
{
    ImGui_ImplMetal_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool MetalRenderer::renderBegin()
{
    if (_renderStarted) return false;
    _renderStarted = true;

    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();

    int width, height;
    glfwGetFramebufferSize(_win.glfwWindow(), &width, &height);
    _objc->layer.drawableSize = CGSizeMake(width, height);
    _objc->curDrawable = [_objc->layer nextDrawable];

    _objc->curCommandBuffer = [_objc->commandQueue commandBuffer];
    //_objc->renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(clear_color[0] * clear_color[3], clear_color[1] * clear_color[3], clear_color[2] * clear_color[3], clear_color[3]);
    _objc->renderPassDescriptor.colorAttachments[0].texture = _objc->curDrawable.texture;
    _objc->renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
    _objc->renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
    _objc->curRenderEncoder = [_objc->curCommandBuffer renderCommandEncoderWithDescriptor:_objc->renderPassDescriptor];
    [_objc->curRenderEncoder pushDebugGroup:@"ImGui demo"];

    // Start the Dear ImGui frame
    ImGui_ImplMetal_NewFrame(_objc->renderPassDescriptor);
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    return true;
}

bool MetalRenderer::renderEnd()
{
    if (!_renderStarted) return false;
    _renderStarted = false;

    // Rendering
    ImGui::Render();
    ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), _objc->curCommandBuffer, _objc->curRenderEncoder);

    [_objc->curRenderEncoder popDebugGroup];
    [_objc->curRenderEncoder endEncoding];

    [_objc->curCommandBuffer presentDrawable:_objc->curDrawable];
    [_objc->curCommandBuffer commit];

    // release temp objects
    [_objc->curDrawable release];
    [_objc->curCommandBuffer release];
    [_objc->curRenderEncoder release];

    return true;
}

