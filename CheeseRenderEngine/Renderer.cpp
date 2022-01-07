#include "Renderer.h"

ge::Renderer::Renderer()
{
	commonUBO.name = "CRE_common";

}

void ge::Renderer::update()
{
	//Write all entity positions into the ubo
	commonUBO.bind();
	commonUBO.setValue("CRE_world", world);
	for (int i = 0; i < totalRenderables; i++) {
		std::string value = "entities[" + std::to_string(i) + "].model";
		commonUBO.setValue(value, commonUBORendEnts[i].model);

		value = "entities[" + std::to_string(i) + "].layer";
		commonUBO.setValue(value, commonUBORendEnts[i].layer);

		value = "entities[" + std::to_string(i) + "].atlasSize";
		commonUBO.setValue(value, commonUBORendEnts[i].atlasSize);

		value = "entities[" + std::to_string(i) + "].uvOffset";
		commonUBO.setValue(value, commonUBORendEnts[i].uvOffset);
	}
}
