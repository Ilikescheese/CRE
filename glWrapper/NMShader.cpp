#include "wrapperPch.h"
#include "NMShader.h"
#include "loadFile.h"
#include "UBObj.h"

void OGL::NMShader::m_compile(GLuint shader,const char *shaderType) {
	glCompileShader(shader);

	//Shader compilation checks
	GLint status = 1;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status) {
		int logSize = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
		GLsizei length = logSize;
		GLchar *log = new GLchar[logSize];
		glGetShaderInfoLog(shader, logSize, &length, log);
		std::cerr << shaderType << " shader compilation failure:" << log << '\n';
		delete[] log;
	}
}

void OGL::NMShader::use() const {
	glUseProgram(m_program);
}

const GLuint OGL::NMShader::getObject() const {
	return m_program;
}

/*
	Compiles from source code ***NOT FROM A PATH***
*/
void OGL::NMShader::build(const char *vSource, const char *fSource) {
	GLuint vert = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vert, 1, &vSource, nullptr);
	m_compile(vert, "vertex");
	glShaderSource(frag, 1, &fSource, nullptr);
	m_compile(frag, "fragment");
	m_program = glCreateProgram();
	glAttachShader(m_program, vert);
	glAttachShader(m_program, frag);
	glLinkProgram(m_program);

	//Program linkage checking
	GLint status = 1;
	glGetProgramiv(m_program, GL_LINK_STATUS, &status);
	if (!status) {
		GLsizei logSize = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logSize);
		GLchar *log = new GLchar[logSize];
		glGetProgramInfoLog(m_program, logSize, &logSize, log);
		std::cerr << "GL program linkage failure:" << log << '\n';
		//delete[] log;
	}

	glDeleteShader(vert);
	glDeleteShader(frag);
}

void OGL::NMShader::destroy() {
	glDeleteProgram(m_program);
}

void OGL::NMShader::setMat4(const char *parameter, const glm::mat4 &matrix) {
	glUniformMatrix4fv(glGetUniformLocation(m_program, parameter), 1, GL_FALSE, glm::value_ptr(matrix));
}

void OGL::NMShader::setVec2(const char *parameter, const glm::vec2 &vector) {
	glUniform2f(glGetUniformLocation(m_program, parameter), vector.x, vector.y);
}

void OGL::NMShader::setVec3(const char *parameter, const glm::vec3 &vector) {
	glUniform3f(glGetUniformLocation(m_program, parameter), vector.x, vector.y, vector.z);
}

void OGL::NMShader::setVec4(const char *parameter, const glm::vec4 &vector) {
	glUniform4f(glGetUniformLocation(m_program, parameter), vector.x, vector.y, vector.z, vector.w);
}

void OGL::NMShader::setUniformBlock(const UBObj &ubo) {
	//Connect the shader and the ubo to the same binding point
	unsigned block = glGetUniformBlockIndex(m_program, ubo.name.c_str());
	glUniformBlockBinding(m_program, block, ubo.getBindingPoint());
}

void OGL::NMShader::setInt(const char *parameter, const GLint &integer) {
	glUniform1i(glGetUniformLocation(m_program, parameter), integer);
}

void OGL::NMShader::setHandle(const char *parameter, const GLuint64 &value) {
	glUniformHandleui64ARB(glGetUniformLocation(m_program, parameter), value);
}

OGL::NMShader::NMShader(const char *vShadPath, const char *fShadPath) {
	build(loadFile(vShadPath).c_str(), loadFile(fShadPath).c_str());
}