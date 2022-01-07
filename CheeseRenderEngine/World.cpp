#include "World.h"
#include "Entity.h"

#include "Component.h"
ge::World::World()
{
	const auto entity = world.create();
	world.emplace<glm::vec3>(entity,0,0,0);

	world.emplace<Health>(entity, Health());
	Health &hp = world.get<Health>(entity);
	hp.sayHp();
}
