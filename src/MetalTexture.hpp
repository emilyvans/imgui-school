#pragma once

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

#include "Texture.hpp"

class MetalTexture : public Texture {
private:
    NS::SharedPtr<MTL::Texture> _tex;

public:
    MetalTexture(NS::SharedPtr<MTL::Texture> tex);

    void* inner() const noexcept override;
    int width() const noexcept override;
    int height() const noexcept override;
};
