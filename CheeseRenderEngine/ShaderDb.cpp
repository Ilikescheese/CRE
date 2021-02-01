#include "ShaderDb.h"

OGL::NMShader chre::ShaderDb::create(ShaderType type) {
	switch (type) {
	case ShaderType::Generic:
		return OGL::NMShader("res/shader/Generic.vert", "res/shader/Generic.frag");
		break;
	case ShaderType::Phong:
		return OGL::NMShader("res/shader/Phong.vert", "res/shader/Phong.frag");
		break;
	case ShaderType::Billboard:
		return OGL::NMShader("res/shader/Billboard.vert", "res/shader/Billboard.frag");
		break;
	}
}