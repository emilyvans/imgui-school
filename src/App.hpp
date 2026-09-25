#pragma once

#include <string>

#include <imgui.h>

#include "TextureLoader.hpp"
#include "TextureStore.hpp"

class App {
private:
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    TextureLoader& _texLoader;
    TextureStore _texStore;

    void _loadTexture(const std::string& name, const std::string& path);

public:
    App(TextureLoader& texLoader);

    void draw();
};

