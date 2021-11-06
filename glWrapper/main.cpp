#include "wrapperPch.h"
/*
#include "Shader.h"
#include "VAObj.h"
#include "Texture2DArray.h"
#include "Initializer.h"
#include "Image.h"
#include "drawFunctions.h"

#include "extras/Camera.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

using namespace OGL;

void errCallback(int, const char *message) {
	std::cerr << "GLFW error:" << message << '\n';
}

static void APIENTRY debugCallbackGL(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar *message, const void *userParam) {
	std::cerr << "-------------OpenGL message\n";
	std::cerr << message << '\n';
	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cerr << "Where? API";								break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cerr << "Where? Window System";						break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Where? Shader Compiler";					break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cerr << "Where? Third Party";						break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cerr << "Where? Application";						break;
	case GL_DEBUG_SOURCE_OTHER:           std::cerr << "Where? Other";								break;
	}
	std::cerr << '\n';
	switch (type) {
	case GL_INVALID_ENUM:                  std::cerr << "Type: GL_INVALID_ENUM";					break;
	case GL_INVALID_VALUE:                 std::cerr << "Type: GL_INVALID_VALUE";					break;
	case GL_INVALID_OPERATION:             std::cerr << "Type: GL_INVALID_OPERATION";				break;
	case GL_OUT_OF_MEMORY:                 std::cerr << "Type: GL_OUT_OF_MEMORY";					break;
	case GL_INVALID_FRAMEBUFFER_OPERATION: std::cerr << "Type: GL_INVALID_FRAMEBUFFER_OPERATION";	break;
	default:							   std::cerr << "Type: code=" << type;						break;
	}
	std::cerr << '\n';
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cerr << "Severity: high";								break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cerr << "Severity: medium";							break;
	case GL_DEBUG_SEVERITY_LOW:          std::cerr << "Severity: low";								break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cerr << "Severity: notification";						break;
	}
	std::cerr << "\n--------------------------\n";
}

/*
	TODO: decide which objects are destroy()'d or deconstruct when out of scope
	TODO: clean up headers, make a pch
	TODO: Look into binary uploads for caching shaders
*/

/*
int main() {
	//OpenGL setup
	glfwSetErrorCallback(errCallback);
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(800, 600, "Wrapper", nullptr, nullptr);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cerr << "Failed to load GLAD!\n";

	glDebugMessageCallback(debugCallbackGL, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE); // disable notifications
	//Init code for OGL wrapper
	Initializer init;

	std::vector<float> vertices = {
		// positions          // colors           // texture coords
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // top left 
	};

	std::vector<unsigned> indices = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	VAObj model(vertices, indices, { { 3 }, { 3 }, { 2 } });

	ShaderProg vS("res/a.vert", ShaderProgType::Vertex);
	ShaderProg fS("res/a.frag", ShaderProgType::Fragment);
	Shader red(vS, fS);
	//NMShader red("res/a.vert", "res/a.frag");

	Texture2DArray texture(256, 256);

	Image missing("res/missing.png");
	texture.add(missing);

	texture.genHandle();
	red.use();
	red.setHandle("tex", texture.handle);
	red.setInt("layer", 0);

	float cur = 0, prev = 0, delta = 0;
	Camera cam(window, 800, 600);

	RenderCmd command;
	command.end = 6;
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.4, 0.4, 0.4, 1);

		prev = cur;
		cur = glfwGetTime();
		delta = cur - prev;
		red.use();
		cam.update(red, window, delta);

		model.use();
		drawElements(command);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	red.destroy();
	texture.destroy();
	model.destroy();
	return 0;
}*/