#include "Logger.h"

void APIENTRY Logger::m_oglDbgCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar *message, const void *userParam) {
	Logger::err("GL message---------------");
	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		Logger::err("Where? API");
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		Logger::err("Where? Window System");
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		Logger::err("Where? Shader Compiler");
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		Logger::err("Where? Third Party");
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		Logger::err("Where? Application");
		break;
	case GL_DEBUG_SOURCE_OTHER:
		Logger::err("Where? Other");
		break;
	}
	switch (type)
	{
	case GL_INVALID_ENUM:
		Logger::err("Type: GL_INVALID_ENUM");
		break;
	case GL_INVALID_VALUE:
		Logger::err("Type: GL_INVALID_VALUE");
		break;
	case GL_INVALID_OPERATION:
		Logger::err("Type: GL_INVALID_OPERATION");
		break;
	case GL_OUT_OF_MEMORY:
		Logger::err("Type: GL_OUT_OF_MEMORY");
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		Logger::err("Type: GL_INVALID_FRAMEBUFFER_OPERATION");
		break;
	default:
		Logger::err("Type: code=", type);
		break;
	}
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		Logger::err("Severity: high");
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		Logger::err("Severity: medium");
		break;
	case GL_DEBUG_SEVERITY_LOW:
		Logger::err("Severity: low");
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		Logger::err("Severity: notification");
		break;
	}
	Logger::err(message);
	Logger::err("------------------------------");
}

void Logger::omitSeverityLevel(levels level) const {
	switch (level)
	{
	case levels::nothing: // Omit nothing from logs
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_FALSE);
		break;
	case levels::notification: // Omit notifications from logs
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
		break;
	case levels::low: // Omit low level errors from logs
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_LOW, 0, nullptr, GL_FALSE);
		break;
	case levels::med: // Omit medium level errors from logs
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, nullptr, GL_FALSE);
		break;
	case levels::high: // Omit high level errors from logs
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_FALSE);
		break;
	}
}

Logger::Logger() {
	glDebugMessageCallback(m_oglDbgCallback, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}