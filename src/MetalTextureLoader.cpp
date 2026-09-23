#include "MetalTextureLoader.hpp"

#include <cstdint>

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

#include "Metal/MTLPixelFormat.hpp"
#include "MetalTexture.hpp"

MetalTextureLoader::MetalTextureLoader()
{ }

MetalTextureLoader::MetalTextureLoader(NS::SharedPtr<MTL::Device> device)
    : _device{device}
{ }

void MetalTextureLoader::setDevice(NS::SharedPtr<MTL::Device> device)
{
    _device = device;
}

std::unique_ptr<Texture> MetalTextureLoader::loadFromMemory(const void *data, size_t size)
{
    std::uint8_t* imageData = nullptr;
    int width, height;

    if (!_loadDataFromMemory(data, size, imageData, &width, &height, nullptr)) {
        return nullptr;
    }

    auto texDesc = MTL::TextureDescriptor::alloc()->init();
    texDesc->setPixelFormat(MTL::PixelFormatRGBA8Unorm);
    texDesc->setWidth(width);
    texDesc->setHeight(height);

    auto tex = _device->newTexture(texDesc);
    MTL::Region region(0, 0, 0, width, height, 1);
    tex->replaceRegion(region, 0, imageData, 4 * width);

    return std::make_unique<MetalTexture>(NS::TransferPtr(tex));
}
