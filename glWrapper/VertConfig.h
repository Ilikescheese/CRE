#pragma once
#include "wrapperPch.h"
namespace OGL {
	struct VConf {
		unsigned componentCount = 0;
		std::size_t size = 0;
		VConf(unsigned count) : size(sizeof(float) * count), componentCount(count) {};
		VConf(unsigned count, std::size_t sizeOfComponents) : size(sizeOfComponents), componentCount(count) {};
	};
}