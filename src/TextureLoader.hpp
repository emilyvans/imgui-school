#pragma once

#include "Texture.hpp"

#include <memory>

class TextureLoader {
public:
    virtual std::unique_ptr<Texture> loadFromMemory(const void* data, size_t size) = 0;
};
