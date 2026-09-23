#include "TextureStore.hpp"

#include <memory>
#include <string>

#include "Texture.hpp"

bool TextureStore::store(const std::string& key, std::unique_ptr<Texture> tex)
{
    if (tex == nullptr || _textures.contains(key)) {
        return false;
    }

    _textures.insert({key, std::move(tex)});

    return true;
}

Texture* TextureStore::retrieve(const std::string& key) const
{
    return _textures.at(key).get();
}

bool TextureStore::has(const std::string& key) const noexcept {
    return _textures.contains(key);
}

