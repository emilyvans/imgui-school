#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Texture.hpp"

class TextureStore {
private:
    std::unordered_map<std::string, std::unique_ptr<Texture>> _textures;

public:
    bool store(const std::string& key, std::unique_ptr<Texture> tex);

    Texture* retrieve(const std::string& key) const;

    bool has(const std::string& key) const noexcept;
};
