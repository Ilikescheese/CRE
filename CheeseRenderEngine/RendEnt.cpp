#include "RendEnt.h"

unsigned chre::RendEnt::getFormatAttribCount() {
	unsigned count = 0;
	for (auto &i : mesh->format)
		count += i.componentCount;
	return count;
}

chre::RendEnt::RendEnt(Mesh *geom, Material *mat) : mesh(geom), material(mat) {}