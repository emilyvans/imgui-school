#pragma once

#include <string>

#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>

enum WindowType {
    OpenGL,
    NoApi,
    Metal = NoApi,
};

template<WindowType type>
class Window
{
private:
    GLFWwindow* _window = nullptr;

    inline void _windowHintsOpenGL()
    {
#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100 (WebGL 1.0)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
        // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
        // GL 3.2 + generally GLSL 150
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#else
        // GL 3.0 + generally GLSL 130
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
        // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only
#endif
    }

public:
    Window(int width, int height, const std::string& title)
    {
        // window hints
        if constexpr(type == WindowType::Metal) {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        } else if constexpr(type == WindowType::OpenGL) {
            _windowHintsOpenGL();
        }

        _window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (_window == nullptr)
            throw std::runtime_error{"Could not create GLFW window"};

        if constexpr(type == WindowType::OpenGL) {
            glfwMakeContextCurrent(_window);
            glfwSwapInterval(1); // vsync
        }
    }

    ~Window() noexcept
    {
        glfwDestroyWindow(_window);
    }

    bool shouldClose() noexcept
    {
        return glfwWindowShouldClose(_window);
    }

    GLFWwindow* glfwWindow() noexcept
    {
        return _window;
    }
};

