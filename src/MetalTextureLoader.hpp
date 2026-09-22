#pragma once

#include <memory>

#include "TextureLoader.hpp"
#include "renderer/MetalRenderer.hpp"
#include "Texture.hpp"

class MetalTextureLoader : public TextureLoader {
private:
    NS::SharedPtr<MTL::Device> _device;

public:
    MetalTextureLoader(MetalRenderer& renderer);
    MetalTextureLoader(NS::SharedPtr<MTL::Device> device);

    std::unique_ptr<Texture> loadFromMemory(const void* data, size_t size) override;
};

