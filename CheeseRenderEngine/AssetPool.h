#pragma once
#include "MaterialManager.h"
#include "ShaderDb.h"
#include "TextureManager.h"
namespace chre {
	class AssetPool
	{
	public:
		static inline TextureManager texMan;
		static inline MaterialManager matMan;
		static inline ShaderDb shaderDb;
		static void setup();
	};
}


