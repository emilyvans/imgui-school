#pragma once

#include <memory>

#include <stb_image.h>

#include "Texture.hpp"
#include "Utils.hpp"

using StbiPtr = Utils::StbiPtr;

class TextureLoader {
protected:
    virtual bool _loadImageFromMemory(const void* data, size_t dataSize,
                                      StbiPtr& pixelData, int* width, int* height,
                                      int* channels);

public:
    virtual std::unique_ptr<Texture> loadFromMemory(const void* data, size_t size) = 0;
};
