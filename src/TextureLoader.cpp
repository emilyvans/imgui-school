#include "TextureLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Utils.hpp"

using StbiPtr = Utils::StbiPtr;

bool TextureLoader::_loadImageFromMemory(const void* data, size_t dataSize,
                                         StbiPtr& pixelData, int* width, int* height,
                                         int* channels) {
    pixelData = StbiPtr{
        stbi_load_from_memory(reinterpret_cast<const unsigned char*>(data),
                              static_cast<int>(dataSize), width, height, channels, 4)};

    return pixelData != nullptr;
}
