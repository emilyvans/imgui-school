#ifndef INCLUDE_SRC_APP_H_
#define INCLUDE_SRC_APP_H_
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

class app {
private:
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	GLFWwindow *window;

public:
	app();
	void update();
	void run();
	virtual ~app();
};

#endif // INCLUDE_SRC_APP_H_
