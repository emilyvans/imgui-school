#include "GLTexture.hpp"

#include <OpenGL/gl.h>

GLTexture::GLTexture(GLuint texId, int width, int height)
    : _tex{texId}, _width{width}, _height{height}
{
}

void* GLTexture::inner() const noexcept
{
    return reinterpret_cast<void*>(_tex);
}

int GLTexture::width() const noexcept
{
    return _width;
}

int GLTexture::height() const noexcept
{
    return _height;
}
