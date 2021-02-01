#pragma once
#include "glWrapper/NMShader.h"
#include "glWrapper/loadFile.h"

namespace chre {
	//A material acts as an interface for a particular shader
	//This class acts as a skeleton for other interfaces
	class Material
	{
		unsigned m_drawIdCounter = 0;
	public:
		unsigned getDrawId();
		OGL::NMShader shader;
		Material() = default;
		Material(Material&) = delete;
		Material(Material &&rhs) noexcept = default;
		void destroy();
	};
}


