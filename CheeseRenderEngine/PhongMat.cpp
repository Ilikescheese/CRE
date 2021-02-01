#include "PhongMat.h"

#include "AssetPool.h"
chre::PhongMat::PhongMat() {
	shader = AssetPool::shaderDb.create(ShaderType::Phong);
}
