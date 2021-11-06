#include "wrapperPch.h"
#include "Texture2D.h"

void OGL::Texture2D::genHandle(){
	handle = glGetTextureHandleARB(m_object); // get handle
	glMakeTextureHandleResidentARB(handle);
	immutable = true;
}

void OGL::Texture2D::delHandle() const {
	glMakeTextureHandleNonResidentARB(handle);
}

OGL::Texture2D::Texture2D(Image img, bool useMips) {
	glCreateTextures(GL_TEXTURE_2D,1,&m_object);
	glTextureParameteri(m_object, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_object, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(m_object, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(m_object, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureStorage2D(m_object, 1, GL_RGBA8, img.width, img.height);
	glTextureSubImage2D(m_object, 0, 0, 0, img.width, img.height, GL_RGBA, GL_UNSIGNED_BYTE, img.data);

	if (useMips)
		glGenerateTextureMipmap(m_object);
}

void OGL::Texture2D::use(unsigned slot) const {
	glBindTextureUnit(slot, m_object);
}

void OGL::Texture2D::destroy() const {
	delHandle();
	glDeleteTextures(1,&m_object);
}
