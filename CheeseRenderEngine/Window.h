#pragma once
#include "glWrapper/wrapperPch.h"

class Window
{
	GLFWwindow *m_window = nullptr;
	void m_setup();
public:
	GLFWwindow *getGlfwWin() const;
	const GLenum minVersionGL = 4,
		majVersionGL = 5;

	unsigned width, height;
	const char *title = nullptr;
	bool isOpen() const;
	void update() const;

	Window(const char *winTitle, unsigned w, unsigned h);
	Window();
	~Window();
};