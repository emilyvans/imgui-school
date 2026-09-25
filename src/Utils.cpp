#include "Utils.hpp"

#include <imgui.h>

#include <stb_image.h>

#include "Texture.hpp"

namespace Utils {
    void StbiFree::operator()(stbi_uc* data) {
        if (data)
            stbi_image_free(data);
    }

    ImVec2 getDimensions(const Texture& tex) {
        return ImVec2{static_cast<float>(tex.width()), static_cast<float>(tex.height())};
    }
} // namespace Utils
