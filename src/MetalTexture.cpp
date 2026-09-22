#include "MetalTexture.hpp"

MetalTexture::MetalTexture(MTL::Texture* tex)
    : _tex{NS::TransferPtr(tex)}
{
}


void* MetalTexture::inner() const noexcept
{
    return reinterpret_cast<void*>(_tex.get());
}

int MetalTexture::width() const noexcept
{
    return _tex->width();
}

int MetalTexture::height() const noexcept
{
    return _tex->height();
}
