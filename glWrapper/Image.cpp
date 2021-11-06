#include "wrapperPch.h"
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

OGL::Image::Image(const char *path) {
	stbi_set_flip_vertically_on_load(true);
	name = path;
	data = stbi_load(path, &width, &height, &nChannels, STBI_rgb_alpha);
	if (!data)
		std::cerr << "Failed to load image from path '" << path << "'!\n";
}

void OGL::Image::destroy() {
	if (data)
		stbi_image_free(data);
}
