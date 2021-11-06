#pragma once
#include "wrapperPch.h"
#include "loadFile.h"
//Objects encapsulating vertex shaders and fragment shaders
//To be used in conjunction with OGL::Shader
namespace OGL {
	enum class ShaderProgType {
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER
	};
	class ShaderProg {
		void m_check(); //check for link/compilation and output to log
	public:
		GLuint object;
		ShaderProg(const char *path, ShaderProgType type);
		ShaderProg(ShaderProg &) = delete;
		~ShaderProg();
	};
}