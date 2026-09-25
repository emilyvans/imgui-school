#include "MetalTexture.hpp"

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

MetalTexture::MetalTexture(NS::SharedPtr<MTL::Texture> tex)
    : _tex{tex} {}

void* MetalTexture::inner() const noexcept {
    return reinterpret_cast<void*>(_tex.get());
}

int MetalTexture::width() const noexcept {
    return _tex->width();
}

int MetalTexture::height() const noexcept {
    return _tex->height();
}
