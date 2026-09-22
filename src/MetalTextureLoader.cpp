#include "MetalTextureLoader.hpp"

#include "Metal/MTLTypes.hpp"
#include "MetalTexture.hpp"

MetalTextureLoader::MetalTextureLoader(MetalRenderer& renderer)
    : _device{renderer.device()}
{
}

MetalTextureLoader::MetalTextureLoader(NS::SharedPtr<MTL::Device> device)
    : _device{device}
{
}

std::unique_ptr<Texture> MetalTextureLoader::loadFromMemory(const void *data, size_t size)
{
    int width;
    int height;

    void* imageData;
    int bytesPerRow;

    auto texDesc = MTL::TextureDescriptor::alloc()->init();
    texDesc->setWidth(width);
    texDesc->setHeight(height);

    auto tex = _device->newTexture(texDesc);
    MTL::Region region(0, 0, 0, width, height, 1);
    tex->replaceRegion(region, 0, imageData, bytesPerRow);

    return std::make_unique<MetalTexture>(tex);
}
