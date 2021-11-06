#pragma once
#include "wrapperPch.h"

/*
	Non modular shader

	A traditional monolithic shader program, fragment and vertex shaders are grouped together
*/
namespace OGL {
	class UBObj;
	class NMShader
	{
		GLuint m_program;
		void m_compile(GLuint shader, const char *shaderType);
	public:
		const GLuint getObject() const; //Get the underlying gl object
		
		void build(const char *vSource, const char *fSource); //Compiles from source *not* from a path. Overwrites previous shader handles, if the shader changes frequently then use OGL::Shader
		void destroy(); // Deletes the object
		virtual void use() const;
		
		void setUniformBlock(const UBObj &ubo); //This function only connects the block in the shader to the buffer. To set values you must do so through the ubo

		void setInt(const char *parameter, const GLint &integer);
		void setHandle(const char *parameter, const GLuint64 &value);
		void setVec2(const char *parameter, const glm::vec2 &vector);
		void setVec3(const char *parameter, const glm::vec3 &vector);
		void setVec4(const char *parameter, const glm::vec4 &vector);
		void setMat4(const char *parameter, const glm::mat4 &matrix);
		NMShader(const char *vShadPath, const char *fShadPath); // Load shader from path
		NMShader() = default;
		
		//NMShader(NMShader &&rhs) noexcept = default;
		//NMShader(const NMShader &) = delete;
		//NMShader& operator=(NMShader&) = delete;
	};
}