#pragma once
#include <unordered_map>
#include "Logger.h"
#include "glWrapper/NMShader.h"
namespace chre {
	enum class ShaderType {
		Generic, //Just a flat texture
		Phong,	 //Phong lit shader
		Billboard //forward facing sprite
	};

	class ShaderDb {
	public:
		OGL::NMShader create(ShaderType type); // Create a new shader of a certain type
	};
}