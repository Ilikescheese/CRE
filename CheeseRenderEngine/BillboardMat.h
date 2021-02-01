#pragma once
#include "GenericMat.h"
namespace chre {
	class BillboardMat : public GenericMat
	{
	public:
		void faceForward(glm::mat4 &model, const glm::vec3 &position,const glm::vec3 &camPos, const glm::vec3 &camUp);
		BillboardMat();
	};
}

