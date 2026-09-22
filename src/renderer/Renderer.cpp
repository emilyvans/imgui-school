#include "renderer/Renderer.hpp"

#include <functional>

bool Renderer::render(std::function<void()> update)
{
    if (!renderBegin()) return false;

    update();

    return renderEnd();
}

