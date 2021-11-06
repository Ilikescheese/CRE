#include "TextureManager.h"
#include "Texture.h"
#include "Logger.h"

#define STB_RECT_PACK_IMPLEMENTATION
#include "../CRE/CheeseRenderEngine/deps/stb/stb_rect_pack.h"
#include <filesystem>

//TODO: redo the whole class

bool chre::TextureManager::m_pack(unsigned &rectCount, std::vector<OGL::Image> &images) {
	//Pack the images
	stbrp_context context;
	stbrp_node *nodes = new stbrp_node[atWidth];
	stbrp_init_target(&context, atWidth, atHeight, nodes, atWidth);
	stbrp_pack_rects(&context, m_rects, rectCount);

	bool again = false;
	unsigned newCount = rectCount;
	for (int i = 0; i < rectCount; i++) {
		OGL::Image &image = images[m_rects[i].id];
		if (m_rects[i].was_packed) {
			//TODO: more than one atlas will require the atlas pointer be set to that of the current atlas it is in
			Texture current { m_rects[i].x, m_rects[i].y, m_rects[i].w, m_rects[i].h, m_curLayer, &atlas, this };
			m_textures.insert(std::pair<std::string, Texture>(image.name, current));
			atlas.add(image, current.x, current.y, current.layerIndex);
			newCount--;
		}
		else {
			if (image.width > atWidth || image.height > atHeight)
				Logger::info(image.name, " could not be packed into the texture atlas, the dimensions exceed that of the atlas.");
			else
				again = true;
		}
	}
	rectCount = newCount;
	delete[] nodes;
	return again;
}

void chre::TextureManager::setContents(std::vector<OGL::Image> &images) {
	//Used for calculating the number of layers needed
	//This algorithim assumes that the area within xOffset * yOffset has already been occupied i.e if a bin packing solution has been used
	unsigned w = 0;
	unsigned h = 0;
	unsigned layerCount = 1;

	for (auto &image : images) {
		if (image.width <= atWidth || image.height <= atHeight) {
			w += image.width;
			h += image.height;
			if (w >= atWidth || h >= atHeight) {
				layerCount++;
				w = 0;
				h = 0;
			}
		}
	}

	atlas.layerW = atWidth;
	atlas.layerH = atHeight;
	atlas.setup(layerCount);

	//Create the first rect array
	unsigned rectCount = images.size();
	m_rects = new stbrp_rect[rectCount];
	for (int i = 0; i < rectCount; i++)
		m_rects[i] = { i, static_cast<unsigned short>(images[i].width), static_cast<unsigned short>(images[i].height) };

	while (m_pack(rectCount, images)) {
		m_curLayer++;

		//Copy from m_rects to rects
		stbrp_rect *rects = new stbrp_rect[rectCount];
		unsigned counter = 0;
		for (int i = 0; i < images.size(); i++) {
			if (!m_rects[i].was_packed) {
				OGL::Image &cur = images[m_rects[i].id];
				rects[counter] = { i, static_cast<unsigned short>(cur.width), static_cast<unsigned short>(cur.height) };
				counter++;
			}
		}
		delete[] m_rects;
		m_rects = rects;
	}
	delete[] m_rects;
	atlas.genHandle();
}

chre::Texture chre::TextureManager::get(const std::string &name) {
	std::unordered_map<std::string, Texture>::iterator result = m_textures.find(name);
	if (result != m_textures.end())
		return result->second;
	Logger::err("Failed to find a texture asset named '", name, '\'');
	return Texture();
}

/*
chre::TextureManager::TextureManager(std::vector<OGL::Image> &images, unsigned width, unsigned height) :atWidth(width),atHeight(height){
	setContents(images);
}
*/
void chre::TextureManager::destroy() {
	atlas.destroy();
}