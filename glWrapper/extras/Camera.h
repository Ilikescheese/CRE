#pragma once
#include "../wrapperPch.h"

namespace OGL {
	class NMShader;
}

class Camera
{
	static inline void m_cursor(GLFWwindow *window, double xPos, double yPos);
	void m_calcDirs();
	bool m_firstMouse = true;
	unsigned m_winW,m_winH;
public:
	glm::vec3 position = { 0, 0, 3 };
	glm::vec3 front = { 0, 0, -1 };
	glm::vec3 upDir = { 0, 1, 0 };
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 dir;

	float pitch = 45, yaw = -90, roll = 0;
	float prevCursX, prevCursY, cursXOffset, cursYOffset;
	float sensitivity = .1;
	float speed = 2.5;

	glm::mat4 update(GLFWwindow *window, float delta); //Set shader values
	Camera(GLFWwindow *window, unsigned wWidth, unsigned wHeight);
};

