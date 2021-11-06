#pragma once
#include "wrapperPch.h"
#include "VertConfig.h"
#include "RenderCmd.h"
namespace OGL {
	class VAObj
	{
		inline static GLuint m_bindingPointCounter = 0;
		GLuint m_bindingPoint;
		GLuint m_vao;
		GLuint m_buffers[2]; // vbo|ebo 
		void m_setLayout(const std::initializer_list<VConf> &list);
		void m_super();
		VAObj(unsigned setter); // Used by OGL::Initializer to set the binding point to zero
	public:
		friend class Initializer;

		enum bufNames {
			vbo, ebo
		};

		void use() const;

		//Do not call if the object has been constructed w/ a non empty constructor
		void create(std::vector<float> &vertices, std::initializer_list<VConf> layout);
		void create(std::vector<float> &vertices, std::vector<unsigned> &indices, std::initializer_list<VConf> layout);

		void destroy() const;

		VAObj(std::vector<float> &vertices, std::initializer_list<VConf> layout);
		VAObj(std::vector<float> &vertices, std::vector<unsigned> &indices, std::initializer_list<VConf> layout);
		VAObj() = default;
		VAObj(VAObj &) = delete;
	};
}
