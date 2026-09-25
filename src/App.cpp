#include "App.hpp"

#include <fstream>
#include <string>
#include <cstdlib>

#include <imgui.h>

#include "Utils.hpp"

App::App(TextureLoader& texLoader)
    : _texLoader{texLoader}
{
    _loadTexture("test", "./assets/test.png");
    _loadTexture("usb", "./assets/usb.jpg");
    _loadTexture("javascript", "./assets/js.jpg");
}

void App::_loadTexture(const std::string& name, const std::string& path)
{
    std::ifstream imgFile{path, std::ios::binary};

    imgFile.seekg(0, std::ios::end);
    size_t siz = imgFile.tellg();
    imgFile.seekg(0, std::ios::beg);

    auto data = new char[siz];
    imgFile.read(data, siz);

    auto tex = _texLoader.loadFromMemory(data, siz);
    if (tex != nullptr)
        _texStore.store(name, std::move(tex));

    delete[] data;
}

void App::draw()
{
    // 1. Show the big demo window (Most of the sample code is in
    // ImGui::ShowDemoWindow()! You can browse its code to learn more about
    // Dear ImGui!).
    if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End
    // pair to create a named window.
    {
        //static float f = 0.0f;
        //static int counter = 0;

        ImGui::Begin("Hello, world!"); // Create a window called "Hello,
                                       // world!" and append into it.

        //ImGui::Text("This is some useful text."); // Display some text (you can
                                                  // use a format strings too)

        ImGui::Checkbox("Demo Window",
                        &show_demo_window); // Edit bools storing our window
                                            // open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        /*
        ImGui::SliderFloat(
                "float", &f, 0.0f,
                1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3(
                "clear color",
                (float *)&clear_color); // Edit 3 floats representing a color

        // Buttons return true when clicked (most widgets return true when edited/activated)
        if (ImGui::Button( "Button")) counter++;

        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
        */

        ImGuiIO &io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / io.Framerate, io.Framerate);

        {
            static const int texCount = 3;
            static const char* const textureNames[texCount] = {"test", "usb", "javascript"};
            static int texIndex = 0;

            ImGui::Combo("Texture", &texIndex, textureNames, texCount);

            if (_texStore.has(textureNames[texIndex])) {
                auto& sampleTex = *_texStore.retrieve(textureNames[texIndex]);

                ImGui::Image(sampleTex.inner(), Utils::getDimensions(sampleTex));
            }
        }

        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window) {
        ImGui::Begin(
                "Another Window",
                &show_another_window); // Pass a pointer to our bool variable
                                   // (the window will have a closing button
                                   // that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");

        if (ImGui::Button("Close Me")) show_another_window = false;

        ImGui::End();
    }
}

