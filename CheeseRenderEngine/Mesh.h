#pragma once
#include "glWrapper/wrapperPch.h"
#include "glWrapper/VertConfig.h"
namespace chre {
	struct Mesh {
		std::initializer_list<OGL::VConf> format;
		std::vector<float> vertices;
		std::vector<unsigned> indices;
	};
}