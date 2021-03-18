#include "Window.h"
#include "Logger.h"

void errCallback(int, const char *msg) {
	Logger::err("GLFW error!", msg);
}

void Window::m_setup() {
	glfwSetErrorCallback(errCallback);
	glfwInit();
	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majVersionGL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minVersionGL);

	glfwMakeContextCurrent(m_window);
	if(!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
		Logger::err("Failed to load");
}

GLFWwindow *Window::getGlfwWin() const {
	return m_window;
}

bool Window::isOpen() const {
	return !glfwWindowShouldClose(m_window);
}

void Window::update() const {
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

Window::Window(const char *windowTitle, unsigned w, unsigned h)
	: width(w), height(h), title(windowTitle) {
	m_setup();
}

Window::Window() : title("title"), width(800), height(600) {
	m_setup();
}

Window::~Window() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
