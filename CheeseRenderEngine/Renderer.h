#pragma once
#include <glm\glm.hpp>

#include "Batcher.h"
#include "glWrapper/UBObj.h"
#include "RendEnt.h"
namespace ge {
	struct CRE_commonUBOData {
		glm::mat4 model;

		int layer;
		glm::vec2 atlasSize;
		glm::vec4 uvOffset;
		chre::RendEnt *rendEnt = nullptr;
	};

	class Renderer
	{
	public:
		const static inline unsigned totalRenderables = 5;


		static inline glm::mat4 world = glm::mat4(1);
		static inline glm::mat4 model = glm::mat4(1);
		static inline OGL::UBObj commonUBO;
		static inline std::vector<CRE_commonUBOData> commonUBORendEnts;
		
		static inline chre::Batcher batcher;
		static void update();

		Renderer();
	};
}

