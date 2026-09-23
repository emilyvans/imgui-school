#include "Utils.hpp"

#include <imgui.h>

#include "Texture.hpp"

namespace Utils {
    ImVec2 getDimensions(const Texture& tex)
    {
        return ImVec2{
            static_cast<float>(tex.width()),
            static_cast<float>(tex.height())
        };
    }
}
