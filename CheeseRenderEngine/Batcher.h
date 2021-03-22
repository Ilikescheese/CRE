#pragma once
#include "glWrapper/VAObj.h"
#include "glWrapper/NMShader.h"
#include "glWrapper/VertConfig.h"
#include "glWrapper/RenderCmd.h"

#include "Mesh.h"
#include "RendEnt.h"

#include "Logger.h"

namespace chre {
	//TODO: move Batch to another header file
	struct Batch {
	public:
		std::vector<float> vertices;
		std::vector<unsigned> indices;

		std::initializer_list<OGL::VConf> *format = nullptr;

		OGL::RenderCmd cmd; //Basic rendering necessities
		//Multi-draw support
		std::vector<OGL::MultiDrawElementsIndirectCmd> elementCmds;
		std::vector<OGL::MultiDrawArraysIndirectCmd> arrayCmds;

		OGL::NMShader *shader = nullptr;
		OGL::VAObj shape;

		Batch(RendEnt &rendEnt)
			: format(&rendEnt.mesh->format), shader(&rendEnt.material->shader),
			vertices(rendEnt.mesh->vertices), indices(rendEnt.mesh->indices), cmd(rendEnt.cmd), elementCmds(rendEnt.elementCmds), arrayCmds(rendEnt.arrayCmds) {
			/*if (!rendEnt.mesh->indices.empty())
				elementCmds.push_back({static_cast<GLuint>(rendEnt.mesh->indices.size()), rendEnt.cmd.instCount, 0, 0,rendEnt.material->getDrawId()});
			else
				arrayCmds.push_back({ static_cast<GLuint>(rendEnt.mesh->vertices.size()), rendEnt.cmd.instCount, 0, rendEnt.material->getDrawId() });
			*/

		}
		Batch(const Batch &rhs)
			: vertices(rhs.vertices), indices(rhs.indices), format(rhs.format),
			shader(rhs.shader), cmd(rhs.cmd), elementCmds(rhs.elementCmds), arrayCmds(rhs.arrayCmds) {
		};

		void destroy() {
			shape.destroy();
			shader->destroy();
		}
	};

	class Batcher
	{
		bool m_isSameFormat(std::vector<OGL::VConf> a, std::vector<OGL::VConf> b);
		bool m_different(RendEnt &item); // If different from the other batches
		Batch *m_target = nullptr;
		std::size_t m_newBatchThresh = 4'194'304; // The size in bytes for the amount of data needed to make a new batch
		std::vector<Batch> m_batches;
	public:
		void add(RendEnt &item);
		void finalise(); //Writes all data for the static RendEnts into vaos
		void render();
		void render(std::vector<OGL::MultiDrawElementsIndirectCmd> &elementCmds);
	};
}
