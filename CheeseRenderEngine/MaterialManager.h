#pragma once
#include <unordered_set>
#include <string>

namespace chre {
	class MaterialManager
	{ 
		std::unordered_set<std::string> m_matDb;
	public:
		template<typename T>
		T *get(const std::string &alias);

		template<typename Mat>
		void add(Mat &&mat, std::string alias);
	};
}


