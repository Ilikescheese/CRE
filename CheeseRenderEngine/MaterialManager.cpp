#include "MaterialManager.h"
#include "Logger.h"

#include "Material.h"

template<typename T>
T *chre::MaterialManager::get(const std::string &alias) {
	auto search = m_matDb.find(alias);
	//if(search != m_matDb.end())
	//	return &search->second;
	Logger::info("TODO: redo class");
	Logger::err("The material manager couldn't find a material with the alias '", alias, '\'');
	return nullptr;
}

template<typename Mat>
void chre::MaterialManager::add(Mat &&mat, std::string alias) {
	try {
 		m_matDb.insert(std::make_pair<std::string,Mat>(std::move(alias),std::move(mat)));
    }
    catch (const std::exception &err) {
		Logger::err("Error adding a new material:",err.what());
	}
}
