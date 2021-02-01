#pragma once
#include "glWrapper/Image.h"
#include "glWrapper/Texture2DArray.h"
#include "Texture.h"

#include <unordered_map>
#include <string>
#include <initializer_list>

class stbrp_rect;
namespace chre {
	class TextureManager
	{
		std::unordered_map<std::string, Texture> m_textures;
		bool m_pack(unsigned &rectCount, std::vector<OGL::Image> &images);

		stbrp_rect *m_rects = nullptr;

		unsigned m_curLayer = 0;
	public:
		const unsigned atWidth = 512, atHeight = 512;
		OGL::Texture2DArray atlas;

		void setContents(std::vector<OGL::Image> &images);
		Texture get(const std::string &name);

		//TextureManager(std::vector<OGL::Image> &images, unsigned width = 512, unsigned height = 512);
		//TextureManager() = default;
		void destroy();
		//would be cool if the max atlas width and height was automatically determined from the images
	};
}

