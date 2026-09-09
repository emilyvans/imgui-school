#include "renderer/RendererBase.hpp"

RendererBase::~RendererBase()
{ }

bool RendererBase::render(std::function<void()> update)
{
    if (!renderBegin()) return false;

    update();

    return renderEnd();
}

