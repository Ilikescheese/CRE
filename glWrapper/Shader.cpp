#include "wrapperPch.h"
#include "Shader.h"

void OGL::Shader::use() const {
	glBindProgramPipeline(m_pipeline);
}

void OGL::Shader::attach(ShaderProg &vProg, ShaderProg &fProg) {
	glUseProgramStages(m_pipeline, GL_VERTEX_SHADER_BIT, vProg.object);
	glUseProgramStages(m_pipeline, GL_FRAGMENT_SHADER_BIT, fProg.object);
}

void OGL::Shader::destroy() const {
	glDeleteProgramPipelines(1, &m_pipeline);
}

OGL::Shader::Shader() {
	glCreateProgramPipelines(1, &m_pipeline);
}

OGL::Shader::Shader(ShaderProg &vProg, ShaderProg &fProg) {
	glCreateProgramPipelines(1, &m_pipeline);
	attach(vProg, fProg);
}
