#include "Material.h"
#include "Logger.h"
unsigned chre::Material::getDrawId() {
    return ++m_drawIdCounter;
}

void chre::Material::destroy() {
	shader.destroy();
}