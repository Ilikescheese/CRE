#pragma once
#include "Material.h"
#include "Mesh.h"
#include "glWrapper/RenderCmd.h"

namespace chre {
	class RendEnt
	{
	public:
		unsigned getFormatAttribCount();

		OGL::RenderCmd cmd;

		//Multi-draw support
		std::vector<OGL::MultiDrawElementsIndirectCmd> elementCmds;
		std::vector<OGL::MultiDrawArraysIndirectCmd> arrayCmds;

		Material *material = nullptr;
		Mesh *mesh = nullptr;
		//3d geometry ptr + format
		RendEnt(Mesh *geom, Material *mat);

		RendEnt() = default;
	};
}


