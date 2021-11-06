#pragma once
#include "wrapperPch.h"
#include "RenderCmd.h"
namespace OGL {
	static inline void drawArrays(RenderCmd &cmd) {
		glDrawArrays(cmd.mode, cmd.begin, cmd.end);
	}
	static inline void drawElements(RenderCmd &cmd) {
		glDrawElements(cmd.mode, cmd.end, cmd.indicesType, nullptr);
	}
	static inline void drawElementsInst(RenderCmd &cmd) {
		glDrawElementsInstanced(cmd.mode, cmd.end, cmd.indicesType, nullptr, cmd.instCount);
	}
	static inline void multiDrawElementsInd(std::vector<MultiDrawElementsIndirectCmd> &cmds,RenderCmd &cmd) {
		glMultiDrawElementsIndirect(cmd.mode,cmd.indicesType,cmds.data(),cmds.size(),0);
	}
	static inline void multiDrawArraysInd(std::vector<MultiDrawArraysIndirectCmd> &cmds, RenderCmd &cmd) {
		glMultiDrawArraysIndirect(cmd.mode, cmds.data(), cmds.size(), 0);
	}
}