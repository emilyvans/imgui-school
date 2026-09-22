#pragma once 

#include <imgui.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "renderer/Renderer.hpp"

class GLRenderer : public Renderer {
private:
    Window<OpenGL>& _win;
    bool _renderStarted = false;

public:
    GLRenderer(Window<OpenGL>& win);
    ~GLRenderer();

    //void render(std::function<void()> update) override;
    bool renderBegin() override;
    bool renderEnd() override;
};

