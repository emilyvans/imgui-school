#include "TextureLoader.hpp"

#include <cstdint>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

bool TextureLoader::_loadDataFromMemory(const void* data, size_t dataSize, std::uint8_t*& pixelData,
                         int* width, int* height, int* channels)
{
    pixelData = stbi_load_from_memory((const unsigned char*)data, (int)dataSize,
            width, height, channels, 4);

    return pixelData != nullptr;
}
