#pragma once

#include <OpenGL/gl.h>

#include "Texture.hpp"

class GLTexture : public Texture {
public:
    GLTexture(GLuint texId, int width, int height);

    void* inner() const noexcept override;
    int width() const noexcept override;
    int height() const noexcept override;

private:
    GLuint _tex;
    int _width;
    int _height;
};

