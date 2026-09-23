#pragma once

#include <memory>

#include <cstdint>

#include "Texture.hpp"

class TextureLoader {
protected:
    virtual bool _loadDataFromMemory(const void* data, size_t dataSize, std::uint8_t*& pixelData, int* width, int* height, int* channels);

public:
    virtual std::unique_ptr<Texture> loadFromMemory(const void* data, size_t size) = 0;
};
