 #pragma once

#include <imgui.h>

class Texture {
public:
    virtual ~Texture();

    /**
     * Returns a pointer to the underlying (inner) texture object.
     * Type of pointer returned will depend on the implementation.
     */
    virtual void* inner() const noexcept = 0;

    /**
     * Returns the width of the texture.
     */
    virtual int width() const noexcept = 0;

    /**
     * Returns the height of the texture.
     */
    virtual int height() const noexcept = 0;
};
