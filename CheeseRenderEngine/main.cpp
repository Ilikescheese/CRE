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


/*
	for alex account

	Include:C:\Users\alex\Documents\GitHub\OpenGLWrapper\glWrapper\deps\glm;C:\Users\alex\Documents\GitHub\OpenGLWrapper\glWrapper\deps\glad\include;C:\Users\alex\Documents\GitHub\OpenGLWrapper\glWrapper\deps\glfw\include;C:\Users\alex\Documents\GitHub\OpenGLWrapper\glWrapper\deps;C:\Users\alex\Documents\GitHub\OpenGLWrapper;deps/stb;extras\PhysX\include/physx;extras\assimp\include;%(AdditionalIncludeDirectories)
	Lib: extras\PhysX\lib;C:\Users\alex\Documents\GitHub\OpenGLWrapper\glWrapper\deps\glfw\lib\Debug\x64;C:\Users\alex\source\repos\CRE\CheeseRenderEngine\x64\Debug;extras\assimp\lib\x64\Debug;%(AdditionalLibraryDirectories)

	https://github.com/NVIDIAGameWorks/PhysX/blob/4.1/physx/snippets/snippetrender/SnippetRender.cpp
	https://github.com/NVIDIAGameWorks/PhysX/blob/4.1/physx/snippets/snippethelloworld/SnippetHelloWorldRender.cpp
	https://github.com/NVIDIAGameWorks/PhysX/blob/4.1/physx/snippets/snippethelloworld/SnippetHelloWorld.cpp

*/

/*
	TODO: Look into binary uploads for caching shaders
	TODO: Use the texture manager in the base engine not the render engine
	TODO: shorten the key names for accessing textures in the texMan class
	TODO:For indirect multi draws, bind and set the indirect buffer object instead of passing it through directly
*/

struct TexLocator {
	int layer;
	glm::vec2 atlasSize;
	glm::vec4 uvOffset;
};

struct CRE_RendEnt {
	glm::mat4 model;
	int layer;
	glm::vec2 atlasSize;
	glm::vec4 uvOffset;
	//TexLocator texLoc;
};
CRE_RendEnt entities[276];

//PhysX
#define PX_PHYSX_STATIC_LIB
#include "PxPhysicsAPI.h"
#include "../snippets/snippetcommon/SnippetPrint.h"
#include "../snippets/snippetcommon/SnippetPVD.h"
#include "../snippets/snippetutils/SnippetUtils.h"
using namespace physx;

PxDefaultAllocator allocator;
PxDefaultErrorCallback errorCallback;
PxFoundation *foundation = nullptr;
PxPhysics *physics = nullptr;
PxDefaultCpuDispatcher *dispatcher = nullptr;
PxScene *scene = nullptr;
PxMaterial *material = nullptr;
PxPvd *pvd = nullptr;
PxReal stackZ = 10.0f;

//Create a dynamic physics object
PxRigidDynamic *createDynamic(const PxTransform &t, const PxGeometry &geometry, const PxVec3 &velocity = PxVec3(0)) {
	PxRigidDynamic *dynamic = PxCreateDynamic(*physics, t, geometry, *material, 10.0f);
	dynamic->setAngularDamping(0.5);
	dynamic->setLinearVelocity(velocity);
	scene->addActor(*dynamic);
	return dynamic;
}

//Creates a stack of boxes
void createStack(const PxTransform &t, PxU32 size, PxReal halfExtent) {
	PxShape *shape = physics->createShape(PxBoxGeometry(halfExtent, halfExtent, halfExtent), *material);
	for (PxU32 i = 0; i < size; i++)
	{
		for (PxU32 j = 0; j < size - i; j++)
		{
			PxTransform localTm(PxVec3(PxReal(j * 2) - PxReal(size - i), PxReal(i * 2 + 1), 0) * halfExtent);

			PxRigidDynamic *body = nullptr;
			body = physics->createRigidDynamic(t.transform(localTm));

			body->attachShape(*shape);
			PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
			scene->addActor(*body);
		}
	}
	shape->release();
}

void initPhysics(bool interactive) {
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);

	pvd = PxCreatePvd(*foundation);
	PxPvdTransport *transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, pvd);

	PxSceneDesc sceneDesc(physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	dispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = dispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	scene = physics->createScene(sceneDesc);

	PxPvdSceneClient *pvdClient = scene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
	material = physics->createMaterial(0.5f, 0.5f, 0.6f);

	PxRigidStatic *groundPlane = PxCreatePlane(*physics, PxPlane(0, 1, 0, 0), *material);
	scene->addActor(*groundPlane);

	for (PxU32 i = 0; i < 5; i++)
		createStack(PxTransform(PxVec3(0, 0, stackZ -= 10.0f)), 10, 2.0f);

	if (!interactive)
		createDynamic(PxTransform(PxVec3(0, 40, 100)), PxSphereGeometry(10), PxVec3(0, -50, -100));
}

void stepPhysics(bool /*interactive*/) {
	scene->simulate(1.0f / 60.0f);
	scene->fetchResults(true);
}

void cleanupPhysics(bool /*interactive*/) {
	PX_RELEASE(scene);
	PX_RELEASE(dispatcher);
	PX_RELEASE(physics);
	if (pvd)
	{
		PxPvdTransport *transport = pvd->getTransport();
		pvd->release();
		pvd = nullptr;
		PX_RELEASE(transport);
	}
	PX_RELEASE(foundation);
}

int main() {
	Window window("CheeseRenderer", 800, 600);
	//Error logging
	Logger logger;
	logger.omitSeverityLevel(Logger::levels::notification);

	chre::Batcher batcher;
	//Architecture
	std::vector<OGL::Image> images = { OGL::Image("res/tex/male_cheaple_sheet.png"), OGL::Image("res/tex/bulb.png"), OGL::Image("res/tex/missing.png") };
	chre::AssetPool::texMan.setContents(images);
	//Assets
	chre::Mesh mesh = loadMesh("res/models/cube.obj");
	mesh.format = { { 3 }, { 3 }, { 2 } };

	//person
	chre::PhongMat material;

	//CRE_common ubo
	glm::mat4 world = glm::mat4(1);
	glm::mat4 model = glm::mat4(1);

	OGL::UBObj ubo("CRE_common");

	chre::Texture tex = chre::AssetPool::texMan.get("res/tex/missing.png");
	material.setTexture(tex);

	chre::RendEnt person(&mesh, &material);
	material.shader.setUniformBlock(ubo);
	ubo.create(material.shader);
	batcher.add(person);

	//Setting UBO entity data
	TexLocator personTexLoc;
	personTexLoc.layer = tex.layerIndex;
	personTexLoc.atlasSize = { tex.atlas->layerW, tex.atlas->layerH };
	personTexLoc.uvOffset = { 0, 0, 256, 256 };// { tex.u, tex.v, tex.x, tex.y };
	//Camera
	Camera cam(window.getGlfwWin(), 800, 600);

	batcher.finalise();

	glEnable(GL_DEPTH_TEST);
	//Delta timing
	float cur = 0, prev = 0, delta = 0;

	//PhysX stuff
	initPhysics(false);

	//Attaching physx to the entities in my render engine
	createStack({ 0, 0, 0 }, 1, 1);

	//Filling in entity data
	for (int i = 0; i < 276; i++) {
		entities[i] = {
			model,
			personTexLoc.layer,
			personTexLoc.atlasSize,
			personTexLoc.uvOffset,
		};
	}
	PxScene *scene = nullptr;
	PxGetPhysics().getScenes(&scene, 1);
	PxU32 nActors = scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);
	if (nActors) {
		std::vector<PxRigidActor *>  actors(nActors);
		scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor **>(&actors[0]), nActors);
		PxShape
	}
	while (window.isOpen()) {
		stepPhysics(false);
		glClearColor(0.5, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Delta timing
		prev = cur;
		cur = glfwGetTime();
		delta = cur - prev;

		//Camera update
		world = cam.update(window.getGlfwWin(), delta);

		//UBO updates
		ubo.bind();

		//lighting 
		material.shader.use();
		material.shader.setVec3("CRE_viewPos", cam.position);
		material.shader.setVec3("CRE_lightPos", { 0, 0, 5 });

		ubo.setValue("CRE_world", world);
		for (int i = 0; i < 276; i++) {
			std::string value = "entities[" + std::to_string(i) + "].model";

			//entities[i].model = glm::translate(model, {});

			value = "entities[" + std::to_string(i) + "].layer";
			ubo.setValue(value, entities[i].layer);

			value = "entities[" + std::to_string(i) + "].atlasSize";
			ubo.setValue(value, entities[i].atlasSize);

			value = "entities[" + std::to_string(i) + "].uvOffset";
			ubo.setValue(value, personTexLoc.uvOffset);
		}
		ubo.unbind();

		batcher.render();
		window.update();
	}
	cleanupPhysics(false);
	return 0;
}