#pragma once
#include "glWrapper/wrapperPch.h"

class Logger
{
	static void APIENTRY m_oglDbgCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
		const GLchar *message, const void *userParam);
public:
	enum levels {
		nothing,
		notification,
		low,
		med,
		high
	};
	static inline void info();
	template<typename T, typename... Args>
	static void info(T type, Args... arguments); // Log info

	static inline void err();
	template<typename T, typename... Args>
	static void err(T type, Args... arguments); // Log errors

	void omitSeverityLevel(levels level) const; // removes messages of x severity from the logs

	Logger();
};

inline void Logger::err() {
	std::cerr << " (ERR)" <<  '\n';
}

inline void Logger::info() {
	std::cout << '\n';
}

template<typename T, typename... Args>
static inline void Logger::err(T type, Args... arguments) {
	std::cerr << type;
	err(arguments...);
}

template<typename T, typename ...Args>
static inline void Logger::info(T type, Args ...arguments) {
	std::cout << type;
	info(arguments...);
}