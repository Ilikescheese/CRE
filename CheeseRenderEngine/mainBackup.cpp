/*#include "glWrapper/wrapperPch.h"
#include "glWrapper/Shader.h"
#include "glWrapper/VAObj.h"
#include "glWrapper/Texture2DArray.h"
#include "glWrapper/Image.h"
#include "glWrapper/drawFunctions.h"
#include "glWrapper/extras/Camera.h"

#include "Window.h"
#include "Logger.h"
#include "RendEnt.h"
#include "Batcher.h"
#include "Texture.h"

#include "GenericMat.h"
#include "PhongMat.h"
#include "extras/loadMesh.h"

#include "BillboardMat.h"
#include "AssetPool.h"

#include "glWrapper/UBObj.h"
#include <array>
*/

/*
	TODO: Look into binary uploads for caching shaders
	TODO: Use the texture manager in the base engine not the render engine
	TODO: shorten the key names for accessing textures in the texMan class
	TODO:For indirect multi draws, bind and set the indirect buffer object instead of passing it through directly
*/
/*
struct TexLocator {
	int layer;
	glm::vec2 atlasSize;
	glm::vec4 uvOffset;
};

struct CRE_RendEnt { //CRE::RendEnt
	glm::mat4 model;
	TexLocator texLoc;
};

#define RENDENTS 1

#include "World.h"
int main() {
	Window window("CheeseRenderer", 800, 600);
	//Error logging
	Logger logger;
	logger.omitSeverityLevel(Logger::levels::notification);

	chre::Batcher batcher;
	//Architecture
	std::vector<OGL::Image> images = { OGL::Image("res/models/castle/tex/castle.png") };
	chre::AssetPool::texMan.setContents(images);
	//Assets
	chre::Mesh mesh = loadMesh("res/models/castle/castle.obj");
	mesh.format = { { 3 }, { 3 }, { 2 } };

	//person
	chre::PhongMat material;

	//CRE_common ubo
	glm::mat4 world = glm::mat4(1);
	glm::mat4 model = glm::mat4(1);

	OGL::UBObj ubo("CRE_common");

	chre::Texture tex = chre::AssetPool::texMan.get("res/models/castle/tex/castle.png");
	material.setTexture(tex);

	chre::RendEnt cube(&mesh, &material);
	cube.elementCmds.push_back(

		{
			(GLuint)mesh.indices.size(),
			RENDENTS, 0, 0
		}
	);
	material.shader.setUniformBlock(ubo);
	ubo.create(material.shader);
	batcher.add(cube);

	//Setting UBO entity data
	TexLocator cubeTexLoc;
	cubeTexLoc.layer = tex.layerIndex;
	cubeTexLoc.atlasSize = { tex.atlas->layerW, tex.atlas->layerH };
	cubeTexLoc.uvOffset = { tex.u, tex.v, tex.x, tex.y };
	//Camera
	Camera cam(window.getGlfwWin(), 800, 600);

	batcher.finalise();

	glEnable(GL_DEPTH_TEST);
	//Delta timing
	float cur = 0, prev = 0, delta = 0;

	CRE_RendEnt cubeEnt = {
		model,
		cubeTexLoc
	};
	std::vector<CRE_RendEnt> entities;
	entities.push_back(cubeEnt);

	//Write all entity positions into the ubo
	ubo.bind();
	ubo.setValue("CRE_world", world);
	for (int i = 0; i < RENDENTS; i++) {
		std::string value = "entities[" + std::to_string(i) + "].model";
		ubo.setValue(value, entities[i].model);

		value = "entities[" + std::to_string(i) + "].layer";
		ubo.setValue(value, entities[i].texLoc.layer);

		value = "entities[" + std::to_string(i) + "].atlasSize";
		ubo.setValue(value, entities[i].texLoc.atlasSize);

		value = "entities[" + std::to_string(i) + "].uvOffset";
		ubo.setValue(value, entities[i].texLoc.uvOffset);
	}
	//ubo.unbind();


	ge::World wrld;
	while (window.isOpen()) {
		glClearColor(0.5, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Delta timing
		prev = cur;
		cur = glfwGetTime();
		delta = cur - prev;

		//Camera update
		world = cam.update(window.getGlfwWin(), delta);

		//Update entities w/ camera
		ubo.setValue("CRE_world", world);

		//lighting 
		material.shader.use();
		material.shader.setVec3("CRE_viewPos", cam.position);
		material.shader.setVec3("CRE_lightPos", cam.position);

		batcher.render(cube.elementCmds);
		window.update();
	}
	return 0;
}*/