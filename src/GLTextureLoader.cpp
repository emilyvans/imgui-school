#include "GLTextureLoader.hpp"

#include <memory>

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "GLTexture.hpp"
#include "Utils.hpp"

std::unique_ptr<Texture> GLTextureLoader::loadFromMemory(const void* data, size_t size) {
    Utils::StbiPtr imageData;
    int width, height;

    if (!_loadImageFromMemory(data, size, imageData, &width, &height, nullptr)) {
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
