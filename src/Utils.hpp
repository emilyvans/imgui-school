#pragma once

#include <memory>

#include <imgui.h>

#include <stb_image.h>

#include "Texture.hpp"

namespace Utils {
    struct StbiFree {
        void operator()(stbi_uc* data);
    };
    using StbiPtr = std::unique_ptr<stbi_uc, StbiFree>;

    ImVec2 getDimensions(const Texture& tex);
}
