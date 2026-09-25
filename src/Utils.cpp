#include "Utils.hpp"

#include "Texture.hpp"

#include <imgui.h>

namespace Utils {
    ImVec2 getDimensions(const Texture& tex) {
        return ImVec2{static_cast<float>(tex.width()), static_cast<float>(tex.height())};
    }
} // namespace Utils

