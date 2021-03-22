#include "glWrapper/wrapperPch.h"
#include "Batcher.h"
#include "Logger.h"
#include "glWrapper/VAObj.h"
#include "glWrapper/drawFunctions.h"
#include <utility>

bool chre::Batcher::m_isSameFormat(std::vector<OGL::VConf> a, std::vector<OGL::VConf> b) {
	for (int i = 0; i < a.size(); i++)
		if (a[i].componentCount != b[i].componentCount)
			return false;
	return true;
}
//TODO: is it worth implementing checks for multi draw buffers?
bool chre::Batcher::m_different(RendEnt &item) {
	bool result = true;
	for (auto &batch : m_batches) {
		//Same shader
		if (item.material->shader.getObject() == batch.shader->getObject()) {
			//Same format
			if (m_isSameFormat(item.mesh->format, *batch.format))
				//Doesn't exceed max batch size
				if (item.mesh->vertices.capacity() + batch.vertices.capacity() < m_newBatchThresh)
					//Same renderCmd
					if (item.cmd == batch.cmd)
						//An index buffer is/isn't present both the mesh and the batch
						if (item.mesh->indices.empty() == batch.indices.empty()) {
							m_target = &batch;
							result = false;
							break;
						}
		}
	}
	return result;
}

void chre::Batcher::add(RendEnt &item) {
	// Different from the other batches
	if (m_different(item))
		m_batches.emplace_back(Batch(item));
	else {
		if (!m_target->indices.empty()) {
			m_target->indices.insert(m_target->indices.end(), item.mesh->indices.begin(), item.mesh->indices.end());

			if (item.elementCmds.empty()) {
				//Convert from a RenderCmd to a multidraw command
				OGL::MultiDrawElementsIndirectCmd command = { item.mesh->vertices.size(), item.cmd.instCount, 0, m_target->vertices.size() / item.getFormatAttribCount(), item.material->getDrawId() };
				m_target->elementCmds.push_back(command);
			}
			else
				m_target->elementCmds.assign(item.elementCmds.begin(), item.elementCmds.end());
		}
		else {
			//If no custom multidraw commands provided just use the RenderCmd
			if (item.arrayCmds.empty()) {
				//Convert from a RenderCmd to a multidraw command
				OGL::MultiDrawArraysIndirectCmd command = { item.mesh->vertices.size(), item.cmd.instCount, m_target->vertices.size() / item.getFormatAttribCount(), item.material->getDrawId() };
				m_target->arrayCmds.push_back(command);
			}
			else
				m_target->arrayCmds.assign(item.arrayCmds.begin(), item.arrayCmds.end());

		}
		m_target->vertices.insert(m_target->vertices.end(), item.mesh->vertices.begin(), item.mesh->vertices.end());
	}
}

void chre::Batcher::finalise() {
	for (auto &i : m_batches) {
		if (!i.indices.empty()) {
			i.shape.create(i.vertices, i.indices, *i.format);
			i.cmd.end = i.elementCmds.size();
		}
		else {
			i.shape.create(i.vertices, *i.format);
			i.cmd.end = i.arrayCmds.size();
		}
	}
}

void chre::Batcher::render() {
	for (auto &i : m_batches) {
		i.shape.use();
		i.shader->use();

		if (!i.indices.empty())
			OGL::multiDrawElementsInd(i.elementCmds, i.cmd);
		else
			OGL::multiDrawArraysInd(i.arrayCmds, i.cmd);
	}
}

void chre::Batcher::render(std::vector<OGL::MultiDrawElementsIndirectCmd> &elementCmds) {
	for (auto &i : m_batches) {
		i.shape.use();
		i.shader->use();
		if (!i.indices.empty())
			OGL::multiDrawElementsInd(elementCmds, i.cmd);
		else
			OGL::multiDrawArraysInd(i.arrayCmds, i.cmd);
	}
}
