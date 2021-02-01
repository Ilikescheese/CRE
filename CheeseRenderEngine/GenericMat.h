#pragma once
#include "Texture.h"
#include "Material.h"

//Supports textures
namespace chre {
	class GenericMat : public Material
	{
	public:
		void setTexture(const Texture &tex);
		GenericMat();
	};
}

