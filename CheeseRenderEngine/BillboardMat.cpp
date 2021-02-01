#include "BillboardMat.h"
#include "AssetPool.h"

chre::BillboardMat::BillboardMat() {
	shader = AssetPool::shaderDb.create(ShaderType::Billboard);
}
