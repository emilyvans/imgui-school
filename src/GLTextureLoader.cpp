#include "GLTextureLoader.hpp"

#include "GLTexture.hpp"
#include "Stbi.hpp"

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <memory>

std::unique_ptr<Texture> GLTextureLoader::loadFromMemory(const void* data, size_t size) {
    Stbi::DataPtr imageData;
    int width, height;

    if (!Stbi::loadFromMemory(data, size, imageData, &width, &height, nullptr)) {
        return nullptr;
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 imageData.get());

    return std::make_unique<GLTexture>(tex, width, height);
}
