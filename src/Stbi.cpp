#include "Stbi.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Stbi {
    void StbiFree::operator()(stbi_uc* data) {
        if (data) {
            stbi_image_free(data);
        }
    }

    bool loadFromMemory(const void* data, size_t dataSize, Stbi::DataPtr& pixelData,
                        int* width, int* height, int* channels) {
        pixelData = Stbi::DataPtr{
            stbi_load_from_memory(reinterpret_cast<const unsigned char*>(data),
                                  static_cast<int>(dataSize), width, height, channels, 4)};

        return pixelData != nullptr;
    }
} // namespace Stbi
