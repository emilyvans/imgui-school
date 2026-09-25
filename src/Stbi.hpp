#pragma once

#include <stb_image.h>

#include <memory>

namespace Stbi {
    struct StbiFree {
        void operator()(stbi_uc* data);
    };
    using DataPtr = std::unique_ptr<stbi_uc, StbiFree>;

    bool loadFromMemory(const void* data, size_t dataSize, DataPtr& pixelData,
                        int* width, int* height, int* channels);
} // namespace Stbi


