#pragma once
#include "glWrapper/wrapperPch.h"
namespace OGL {
	struct Image {
		unsigned char *data = nullptr;
		std::string name;
		int width = 0, height = 0, nChannels;
		Image() = default;
		Image(const char *path);
		void destroy();
	};
}
