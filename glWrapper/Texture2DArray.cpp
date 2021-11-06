#include "wrapperPch.h"
#include "Texture2DArray.h"

void OGL::Texture2DArray::add(Image &image, unsigned xOffset, unsigned yOffset, unsigned z) {
	glTextureSubImage3D(m_object, 0, xOffset, yOffset, z, image.width, image.height, 1, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
	image.destroy();
}

void OGL::Texture2DArray::setup(unsigned numLayers, bool mips) {
	glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &m_object);
	glTextureParameteri(m_object, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_object, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(m_object, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(m_object, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureStorage3D(m_object, 1, GL_RGBA8, layerW, layerH, numLayers);
	if (mips)
		glGenerateTextureMipmap(m_object);
}

OGL::Texture2DArray::Texture2DArray(unsigned width, unsigned height, unsigned depth, bool useMips)
	: layerW(width), layerH(height) {
	setup(depth, useMips);
}

void OGL::Texture2DArray::destroy() const {
	glDeleteTextures(1, &m_object);
}
