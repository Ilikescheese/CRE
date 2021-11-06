#pragma once
#include "wrapperPch.h"
namespace OGL {
	enum RenderMode : GLenum {
		Triangles = GL_TRIANGLES,
		Points = GL_POINTS,
		Lines = GL_LINES
	};
	//Unsigned types
	enum Unsigns : GLuint {
		Int = GL_UNSIGNED_INT,
		Short = GL_UNSIGNED_SHORT,
		Byte = GL_UNSIGNED_BYTE
	};
	struct RenderCmd {
		RenderMode mode = RenderMode::Triangles;
		GLuint begin = 0;
		GLuint end = 0;
		GLuint instCount = 1;
		GLuint indicesType = Unsigns::Int;
		bool operator==(RenderCmd &rhs) {
			return mode == rhs.mode && begin == rhs.begin && end == rhs.end && instCount == rhs.instCount && indicesType == rhs.indicesType;
		}
	};
	struct MultiDrawElementsIndirectCmd { 
		GLuint end = 0; //Number of vertices/indices
		GLuint instCount = 1; //How many copies of the section to make (to be used in conjunction w/ gl_InstanceId)
		GLuint indexBegin = 0; 
		GLuint baseVert = 0;
		GLuint baseInst = 0; //basically the gl_DrawID the section has
	};
	struct MultiDrawArraysIndirectCmd {
		GLuint end = 0; //Number of vertices/indices
		GLuint instCount = 1; //How many copies of the section to make (to be used in conjunction w/ gl_InstanceId)
		GLuint baseVert = 0;
		GLuint baseInst = 0; //basically the gl_DrawID the section has
	};
}