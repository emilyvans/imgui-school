#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

#include "Window.hpp"
#include "renderer/Renderer.hpp"

class MetalRenderer : public Renderer {
private:
    NS::SharedPtr<MTL::Device> _device;
    NS::SharedPtr<MTL::CommandQueue> _commandQueue;
    NS::SharedPtr<CA::MetalLayer> _layer;
    NS::SharedPtr<MTL::RenderPassDescriptor> _renderPassDescriptor;

    CA::MetalDrawable* _curDrawable;
    MTL::CommandBuffer* _curCommandBuffer;
    MTL::RenderCommandEncoder* _curRenderEncoder;

    Window<Metal>& _win;
    bool _renderStarted = false;

public:
    MetalRenderer(Window<Metal>& win);
    ~MetalRenderer();

    NS::SharedPtr<MTL::Device> device() const;

    bool renderBegin() override;
    bool renderEnd() override;
};
