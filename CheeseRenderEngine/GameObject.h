#pragma once
#include "Component.h"

#include <glm\glm.hpp>
#include <glWrapper/UBObj.h>
#include "PhongMat.h"
#include "RendEnt.h"
#include "Mesh.h"

#include "Renderer.h"
namespace ge {
	class GameObject : public Component
	{
	public:
		CRE_commonUBOData uboData;
		static inline OGL::UBObj *ubo = nullptr;
		glm::vec3 position = { 0,0,0 };

		chre::PhongMat material;
		chre::Mesh mesh;
		chre::RendEnt renderable;
		chre::Texture texture;
		const char *textureName = nullptr;

		void addToScene();
		GameObject();
	};
}

