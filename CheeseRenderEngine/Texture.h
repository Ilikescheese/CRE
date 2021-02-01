#pragma once
#include "glWrapper/Texture2DArray.h"
namespace chre {
	class TextureManager;
	struct Texture {
		float x = 0;
		float y = 0;
		float u = 0;
		float v = 0;
		unsigned layerIndex = 0;
		const OGL::Texture2DArray *atlas = nullptr; // The atlas the texture is located in
		const TextureManager *owner = nullptr;
	};
}


