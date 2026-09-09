#pragma once

#include <functional>

class RendererBase {
public:
    virtual ~RendererBase();

    virtual bool render(std::function<void()> update);
    virtual bool renderBegin() = 0;
    virtual bool renderEnd() = 0;
};

