#pragma once

#include <functional>

class Renderer {
public:
    // virtual void* device() const = 0;

    virtual bool render(std::function<void()> update);
    virtual bool renderBegin() = 0;
    virtual bool renderEnd() = 0;
};
