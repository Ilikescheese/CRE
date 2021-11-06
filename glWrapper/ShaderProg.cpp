#include "wrapperPch.h"
#include "ShaderProg.h"

void OGL::ShaderProg::m_check() {
	//TODO: add tesselation & geometry shader support
	GLint target[3] = {
		GL_ACTIVE_PROGRAM,
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER
	};
	//glValidateProgramPipeLine
	for (int i = 0; i < 3; i++) {
		GLint good;
		glGetProgramPipelineiv(target[i], GL_LINK_STATUS, &good);
		if (!good) {
			GLint bufLen;
			glGetProgramPipelineiv(target[i], GL_INFO_LOG_LENGTH, &bufLen);
			GLsizei logLen = bufLen;
			GLchar *log = nullptr;
			glGetProgramPipelineInfoLog(target[i], bufLen, &logLen, log);
			std::cerr << "OGL::Shader failure:" << log << '\n';
		}
	}
}

OGL::ShaderProg::ShaderProg(const char *path, ShaderProgType type) {
	std::string s = OGL::loadFile(path);
	const char *src = s.c_str();
	glProgramParameteri(object, GL_PROGRAM_SEPARABLE, GL_TRUE);
	object = glCreateShaderProgramv((GLenum)type, 1, &src);
	m_check();
}

OGL::ShaderProg::~ShaderProg() {
	glDeleteShader(object);
}

