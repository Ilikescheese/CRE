#include "wrapperPch.h"
#include "VAObj.h"

/*
	TODO:If the same layout is provided, copy the binding point # to other VAObj
*/

void OGL::VAObj::m_setLayout(const std::initializer_list<VConf> &list) {
	unsigned cur = 0;
	std::size_t offset = 0;
	for (const auto &attrib : list) {
		glEnableVertexArrayAttrib(m_vao, cur);
		glVertexArrayAttribFormat(m_vao, cur, attrib.componentCount, GL_FLOAT, GL_FALSE, offset);
		glVertexArrayAttribBinding(m_vao, cur, m_bindingPoint);

		offset += attrib.size;
		cur++;
	}
	glVertexArrayVertexBuffer(m_vao, m_bindingPoint, m_buffers[bufNames::vbo], 0, offset);
	glEnableVertexArrayAttrib(m_vao, m_bindingPoint);
}

OGL::VAObj::VAObj(unsigned setter) {
	m_bindingPointCounter = setter;
}

void OGL::VAObj::m_super() {
	m_bindingPoint = m_bindingPointCounter;
	m_bindingPointCounter++;
	glCreateVertexArrays(1, &m_vao);
	use();
}

void OGL::VAObj::use() const {
	glBindVertexArray(m_vao);
}

void OGL::VAObj::create(std::vector<float> &vertices, std::initializer_list<VConf> layout) {
	m_super();
	//Create vbo and set storage
	glCreateBuffers(1, m_buffers);
	glNamedBufferStorage(m_buffers[bufNames::vbo], vertices.size() * sizeof(vertices[0]), vertices.data(), 0);

	m_setLayout(layout);
}

void OGL::VAObj::create(std::vector<float> &vertices, std::vector<unsigned> &indices, std::initializer_list<VConf> layout) {
	m_super();

	//Create vbo & ebo,set storage
	glCreateBuffers(2, m_buffers);
	glNamedBufferStorage(m_buffers[bufNames::vbo], vertices.size() * sizeof(vertices[0]), vertices.data(), 0);
	glNamedBufferStorage(m_buffers[bufNames::ebo], indices.size() * sizeof(indices[0]), indices.data(), 0);

	//Manually assign ebo storage to element buffer, this doesnt apply to the vbo as the named storage goes to array buffer by default
	glVertexArrayElementBuffer(m_vao, m_buffers[bufNames::ebo]);
	m_setLayout(layout);
}

void OGL::VAObj::destroy() const {
	glDeleteBuffers(2, m_buffers);
	glDeleteVertexArrays(1, &m_vao);
}

OGL::VAObj::VAObj(std::vector<float> &vertices, std::initializer_list<OGL::VConf> layout) {
	m_super();
	//Create vbo and set storage
	glCreateBuffers(1, m_buffers);
	glNamedBufferStorage(m_buffers[bufNames::vbo], vertices.size() * sizeof(vertices[0]), vertices.data(), 0);

	m_setLayout(layout);
}

OGL::VAObj::VAObj(std::vector<float> &vertices, std::vector<unsigned> &indices, std::initializer_list<VConf> layout) {
	m_super();

	//Create vbo & ebo,set storage
	glCreateBuffers(2, m_buffers);
	glNamedBufferStorage(m_buffers[bufNames::vbo], vertices.size() * sizeof(vertices[0]), vertices.data(), 0);
	glNamedBufferStorage(m_buffers[bufNames::ebo], indices.size() * sizeof(indices[0]), indices.data(), 0);

	//Manually assign ebo storage to element buffer, this doesnt apply to the vbo as the named storage goes to array buffer by default
	glVertexArrayElementBuffer(m_vao, m_buffers[bufNames::ebo]);

	m_setLayout(layout);
}