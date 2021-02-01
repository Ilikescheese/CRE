#include "glWrapper/wrapperPch.h"
#include "glWrapper/Shader.h"
#include "glWrapper/VAObj.h"
#include "glWrapper/Texture2DArray.h"
#include "glWrapper/Initializer.h"
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

/*
	**handle errors with exceptions**
	shader uniforms are prefixed "CRE_"
	TODO: give interface blocks to the shaders

	TODO: decide which objects are destroy()'d or deconstruct when out of scope
	TODO: clean up headers, make a pch
	TODO: Look into binary uploads for caching shaders
	TODO: UBOs

	**vertex format (are per shader, certain lighting features are used based on the material's bitset)**

	DefaultMat
		0 = position
		1 = normals
		2 = uvs

	**Shader constants for CRE format**

	//Projection view and model matrices
	CRE_proj
	CRE_view
	CRE_model

	TODO: Use the texture manager in the base engine not the render engine
	TODO: shorten the key names for accessing textures in the texMan class
*/

/*
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	TODO:For indirect multi draws, bind and set the indirect buffer object instead of passing it through directly
	- Check todos in batcher.cpp's add function
	- 











*/
struct TexLocator {
	glm::vec2 atlasSize;
	int layer;
	glm::vec4 uvOffset;
};

struct CRE_RendEnt {
	glm::mat4 model;
	TexLocator texLoc;
};

CRE_RendEnt entities[10];

int main() {
	Window window("CheeseRenderer",800,600);
	//Error logging
	Logger logger;
	logger.omitSeverityLevel(Logger::levels::notification);
	//Init code
	OGL::Initializer init; //Spell intitialiser with an s not a z
	chre::Batcher batcher;

	//Architecture
	std::vector<OGL::Image> images = { OGL::Image("res/tex/male_cheaple_sheet.png"), OGL::Image("res/tex/bulb.png"),OGL::Image("res/tex/missing.png") };
	chre::AssetPool::texMan.setContents(images);
	//Assets
	chre::Mesh mesh = loadMesh("res/models/cheaple.obj");
	mesh.format = {{3},{3},{2}};
		
	glm::mat4 world = glm::mat4(1);
	glm::mat4 model = glm::mat4(1);

	OGL::UBObj ubo;
	int entSize = OGL::UBObj::std140Types::mat4 + OGL::UBObj::std140Types::vec2 + OGL::UBObj::std140Types::vec1 + OGL::UBObj::std140Types::vec4;
	ubo.createStd140("CRE_common", { OGL::UBObj::std140Types::mat4,(OGL::UBObj::std140Types)entSize });

	//person
	chre::PhongMat material;
	material.setTexture(chre::AssetPool::texMan.get("res/tex/male_cheaple_sheet.png"));
	chre::RendEnt person(&mesh,&material);
	material.shader.setUniformBlock(ubo);
	batcher.add(person);
	
	//Light "entity"
	/*glm::mat4 lightModel = glm::mat4(1);
	glm::vec3 lightPos = {0,0,0};
	chre::BillboardMat lightSpr;
	lightSpr.setTexture(chre::AssetPool::texMan.get("res/tex/bulb.png"));
	chre::Mesh plane = loadMesh("res/models/quad.obj");
	plane.format = { { 3 }, { 3 }, { 2 } };
	chre::RendEnt light(&plane,&lightSpr);
	lightSpr.shader.setUniformBlock(ubo);
	batcher.add(light);
	*/

	//Setting UBO entity data
	chre::Texture personTex = chre::AssetPool::texMan.get("res/tex/male_cheaple_sheet.png");
	TexLocator personTexLoc;
	personTexLoc.atlasSize = {personTex.owner->atWidth,personTex.owner->atHeight};
	personTexLoc.layer = personTex.layerIndex;
	personTexLoc.uvOffset = { personTex.x, personTex.y, personTex.u, personTex.v};

	entities[0] = {
		model,
		personTexLoc
	};

	//Camera
	Camera cam(window.getGlfwWin(), 800, 600);

	batcher.finalise();

	glEnable(GL_DEPTH_TEST);
	//Delta timing
	float cur = 0, prev = 0, delta = 0; 

	while (window.isOpen()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.4, 0.4, 0.4, 1);

		//Delta timing
		prev = cur;
		cur = glfwGetTime();
		delta = cur - prev;

		//Camera update
		world = cam.update(window.getGlfwWin(), delta);

		//UBO updates
		ubo.bind();
		ubo.setValue(0, world);
		ubo.setValue(1,entities[0]);
		ubo.unbind();

		//Person shader update
		material.shader.use();
		material.shader.setVec3("CRE_viewPos",cam.position);
		material.shader.setVec3("CRE_lightPos", {0,0,1});
		
		//material.shader.setMat4("entities[0].model",model);
		//Light shader update
		/*lightPos = { cos(cur) * .01, 0, sin(cur) * .01 };
		lightModel = glm::translate(lightModel, lightPos);
		lightSpr.shader.use();
		lightSpr.shader.setMat4("CRE_model", lightModel);
		*/

		batcher.render();
		window.update();
	}
	return 0;
}