 #pragma once
#include "wrapperPch.h"
#include "NMShader.h"
//TODO: Make bindless, support more layouts etc
namespace OGL {
	class UBObj
	{
		static inline unsigned m_bindPointCounter = 0;
		GLuint m_bindingPoint,m_ubo;
		std::unordered_map<std::string,GLuint> m_block;
		const NMShader *m_target = nullptr; // A shader containing a copy of the block
	public:
		GLuint getObject() const;
		unsigned getBindingPoint() const;
		std::string name;
		void bind();
		void unbind();
		void destroy();

		//TODO: functionality for setting the entire block's data with one array of bytes
		//Set a single value if you're setting a struct, set the whereIndex to the location of last variable in the struct
		template<typename T>
		void setValue(std::string uniformName, T value);

		//make sure to target the zeroth index of the array within the ubo
		template<typename T>
		void setArray(std::string uniformName, T value[]);

		void create(const NMShader &shader);
		UBObj(const std::string &blockName) : name(blockName) {};
	};
	template<typename T>
	inline void UBObj::setArray(std::string uniformName, T value[]) {
		std::size_t arrSize = sizeof(value) / sizeof(value[0]);
		auto it = m_block.find(uniformName);
		if (it != m_block.end()) {
			GLint itemSize = 0;
			glGetActiveUniformsiv(m_target->getObject(), 1, &it->second, GL_UNIFORM_SIZE, &itemSize);

			GLint offset = 0;
			glGetActiveUniformsiv(m_target->getObject(), 1, &it->second, GL_UNIFORM_OFFSET, &offset);
			for (int i = offset; i < i + arrSize * itemSize; i += itemSize) {
				glBufferSubData(GL_UNIFORM_BUFFER, i, sizeof(value[0]), &value[i/itemSize]);
			}
		}
		else
			std::cerr << "Couldn't find the uniform named '" << uniformName << '\'' << " within the ubo block" << '\n';
	}
	template<typename T>
	inline void UBObj::setValue(std::string uniformName, T value) {
		auto it = m_block.find(uniformName);
		if(it != m_block.end()){
			GLint offset = 0;
			glGetActiveUniformsiv(m_target->getObject(), 1, &it->second, GL_UNIFORM_OFFSET, &offset);
			glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(value), &value);
		}
		else
			std::cerr << "Couldn't find the uniform named '" << uniformName << '\'' << " within the ubo block" << '\n';
	}
}
