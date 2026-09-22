#pragma once

#include <memory>

#include "TextureLoader.hpp"
#include "Texture.hpp"

class GLTextureLoader : public TextureLoader {
public:
    std::unique_ptr<Texture> loadFromMemory(const void* data, size_t size);
};

