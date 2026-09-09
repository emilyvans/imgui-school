#pragma once

#include <memory>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "renderer/RendererBase.hpp"

class MetalRenderer : public RendererBase {
private:
    struct ObjCStorage;
    std::unique_ptr<ObjCStorage> _objc;

    Window<Metal>& _win;
    bool _renderStarted = false;

public:
    MetalRenderer(Window<Metal>& win);
    ~MetalRenderer();

    bool renderBegin() override;
    bool renderEnd() override;
};
