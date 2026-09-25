#pragma once

#include <memory>

#include "Texture.hpp"
#include "TextureLoader.hpp"

class GLTextureLoader : public TextureLoader {
public:
    std::unique_ptr<Texture> loadFromMemory(const void* data, size_t size);
};
