#include "GenericMat.h"
#include "glWrapper/NMShader.h"
#include "glWrapper/loadFile.h"

#include "AssetPool.h"

void chre::GenericMat::setTexture(const Texture &tex) {
	shader.use();
	//Always assumes the handle is resident
	shader.setHandle("CRE_texAtlas", tex.atlas->handle);
	//shader.setInt("texLoc.layer", tex.layerIndex);
	//shader.setVec2("texLoc.atlasSize", { tex.owner->atWidth, tex.owner->atHeight });
	//
	//shader.setVec4("texLoc.uvOffset", { tex.x, tex.y, tex.u, tex.v });
}

chre::GenericMat::GenericMat(){
	shader = AssetPool::shaderDb.create(ShaderType::Generic);
}
