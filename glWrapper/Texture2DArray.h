#pragma once
#include "wrapperPch.h"
#include "Texture2D.h"
#include "Image.h"
namespace OGL {
	class Texture2DArray : public Texture2D
	{
	public:
		unsigned layerW, layerH;
		unsigned layerCount = 0;

		void add(Image &image, unsigned xOffset = 0, unsigned yOffset = 0, unsigned z = 0);
		Texture2DArray(unsigned layerW, unsigned layerH, unsigned depth = 32, bool useMips = true);
		Texture2DArray() = default;
		void setup(unsigned numLayers, bool mips = true);
		void destroy() const;
		//Texture2DArray(std::vector<Image> images, unsigned width, unsigned height, unsigned depth = 32, bool useMips = true);
	};
}

