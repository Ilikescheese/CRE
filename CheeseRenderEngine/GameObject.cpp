#include "GameObject.h"

#include "Renderer.h"
#include "Material.h"

#include "AssetPool.h"



void ge::GameObject::addToScene()
{
	Renderer::commonUBO.create(material.shader);
	material.shader.setUniformBlock(Renderer::commonUBO);

	texture = chre::AssetPool::texMan.get("res/models/castle/tex/castle.png");
	material.setTexture(texture);

	renderable.mesh = &mesh;
	renderable.material = &material;
	glm::mat4 model = glm::mat4(1);
	uboData = {
		model,
		static_cast<int>(texture.layerIndex),
		{ texture.atlas->layerW,texture.atlas->layerH },
		{texture.u,texture.v,texture.x,texture.y},
		&renderable
	};



	Renderer::commonUBORendEnts.push_back(uboData);

	renderable.elementCmds.push_back(
		{
			(GLuint)mesh.indices.size(),
			Renderer::totalRenderables, 0, 0
		}
	);

	Renderer::batcher.add(renderable);
}

ge::GameObject::GameObject() {
}
