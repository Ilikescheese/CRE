#pragma once
#include "extras/entt/entt.hpp"
#include <glm/vec3.hpp>
namespace ge {

	class World
	{
	public:
		entt::registry world;
		World();
	};
}

