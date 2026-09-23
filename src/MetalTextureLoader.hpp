#pragma once

#include <memory>

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

#include "TextureLoader.hpp"
#include "Texture.hpp"

class MetalTextureLoader : public TextureLoader {
private:
    NS::SharedPtr<MTL::Device> _device;

public:
    MetalTextureLoader();
    MetalTextureLoader(NS::SharedPtr<MTL::Device> device);

    void setDevice(NS::SharedPtr<MTL::Device> device);

    std::unique_ptr<Texture> loadFromMemory(const void* data, size_t size) override;
};

