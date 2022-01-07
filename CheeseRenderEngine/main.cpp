#include "glWrapper/wrapperPch.h"
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


#include "Renderer.h"

/*
	TODO: Look into binary uploads for caching shaders
	TODO: Use the texture manager in the base engine not the render engine
	TODO: shorten the key names for accessing textures in the texMan class
	TODO:For indirect multi draws, bind and set the indirect buffer object instead of passing it through directly
*/



#define RENDENTS 1

#include "World.h"
#include "Renderer.h"
#include "GameObject.h"
int main() {
	Window window("CheeseRenderer", 800, 600);
	//Error logging
	Logger logger;
	logger.omitSeverityLevel(Logger::levels::notification);
	

	
	//Architecture
	std::vector<OGL::Image> images = { OGL::Image("res/models/castle/tex/castle.png") };
	chre::AssetPool::texMan.setContents(images);
	//Assets
	chre::Mesh mesh = loadMesh("res/models/castle/castle.obj");
	mesh.format = { { 3 }, { 3 }, { 2 } };

	//Camera
	Camera cam(window.getGlfwWin(), 800, 600);


	glEnable(GL_DEPTH_TEST);
	//Delta timing
	float cur = 0, prev = 0, delta = 0;

	ge::World wrld;
	ge::Renderer::commonUBO.name = "CRE_common";
	ge::GameObject castle;
	castle.mesh = mesh;
	castle.texture = chre::AssetPool::texMan.get("res/models/castle/tex/castle.png");
	castle.addToScene();
	ge::Renderer::batcher.finalise();
	while (window.isOpen()) {
		glClearColor(0.5, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Delta timing
		prev = cur;
		cur = glfwGetTime();
		delta = cur - prev;

		ge::Renderer::update();
		//Camera update
		ge::Renderer::world = cam.update(window.getGlfwWin(), delta);

		//Update entities w/ camera
		ge::Renderer::commonUBO.setValue("CRE_world", ge::Renderer::world);

		//lighting 
		castle.material.shader.use();
		castle.material.shader.setVec3("CRE_viewPos", cam.position);
		castle.material.shader.setVec3("CRE_lightPos", cam.position);

		ge::Renderer::batcher.render(castle.renderable.elementCmds);
		window.update();
	}
	return 0;
}