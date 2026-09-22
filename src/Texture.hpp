#pragma once

class Texture {
public:
    virtual ~Texture();

    virtual void* inner() const noexcept = 0;

    virtual int width() const noexcept = 0;
    virtual int height() const noexcept = 0;
};
