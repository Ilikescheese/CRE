#include "wrapperPch.h"
#include "UBObj.h"

void OGL::UBObj::bind() {
	//TODO: Bindless implementation
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
	//Connect GL_UNIFORM_BUFFER target to the binding point
	glBindBufferBase(GL_UNIFORM_BUFFER, m_bindingPoint, m_ubo);
}

void OGL::UBObj::unbind() {
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLuint OGL::UBObj::getObject() const {
	return m_ubo;
}

unsigned OGL::UBObj::getBindingPoint() const {
	return m_bindingPoint;
}

void OGL::UBObj::destroy() {
	glDeleteBuffers(1,&m_ubo);
}

void OGL::UBObj::create(const NMShader &shader) {
	m_target = &shader;
	m_bindingPoint = m_bindPointCounter;
	m_bindPointCounter++;
	
	GLint uniformCount = 0;
	glGetActiveUniformBlockiv(shader.getObject(),m_ubo,GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS,&uniformCount);

	GLuint *indices = new GLuint[uniformCount];
	glGetActiveUniformBlockiv(shader.getObject(), m_ubo, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, reinterpret_cast<GLint *>(indices));

	GLint uniformNameSize = 0;
	glGetProgramiv(shader.getObject(),GL_ACTIVE_UNIFORM_MAX_LENGTH,&uniformNameSize);
	GLchar *curUniformName = new GLchar[uniformNameSize];
	//check for invalid indices & link indices to the names of the uniform
	m_block.reserve(uniformCount);
	for (int i = 0; i < uniformCount; i++) {
		if (indices[i] == GL_INVALID_INDEX)
			std::cerr << "Invalid uniform name at index #" << indices[i] << '\n';

		GLint size = 0;
		GLsizei nameLen = 0;
		GLenum type = GL_NONE;
		glGetActiveUniform(shader.getObject(),indices[i], uniformNameSize,&nameLen,&size,&type,curUniformName);
		m_block.insert(std::make_pair(std::string(curUniformName),indices[i]));
	}
	delete[] curUniformName;

	GLint size = 0;
	glGetActiveUniformBlockiv(shader.getObject(), m_ubo, GL_UNIFORM_BLOCK_DATA_SIZE, &size);

	glGenBuffers(1,&m_ubo);
	bind();
	glBufferData(GL_UNIFORM_BUFFER, size,nullptr,GL_DYNAMIC_DRAW);
	unbind();
	delete[] indices;
}