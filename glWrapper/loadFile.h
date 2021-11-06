#pragma once
#include "wrapperPch.h"

namespace OGL {
	static std::string loadFile(const std::string & path) {
		try {
			std::ifstream file(path, std::ios::in);
			file.exceptions(std::ios::failbit | std::ios::badbit);

			std::stringstream data;
			data << file.rdbuf();

			return data.str();
		}
		catch (const std::ios::failure &err) {
			std::cerr << path << " loading failure err:" << err.what() << '\n';
		}
		return "";
	}
}