#pragma once
#include "glWrapper/wrapperPch.h"

class Window
{
	GLFWwindow *m_window = nullptr;
	void m_setup();
public:
	GLFWwindow *getGlfwWin() const;
	const GLenum majVersionGL = 4, minVersionGL = 6; //4.6

	unsigned width, height;
	const char *title = nullptr;
	bool isOpen() const;
	void update() const;

	Window(const char *winTitle, unsigned w, unsigned h);
	Window();
	~Window();
};