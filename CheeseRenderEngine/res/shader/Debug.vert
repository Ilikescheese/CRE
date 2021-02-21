#version 460 core
layout(location=0) in vec3 aPosition;

out vec3 aColour;

layout(std140) uniform CRE_common {
	mat4 CRE_world;
	vec3 colour;
	vec3 colour2;
};
/*
struct CRE_RendEnt {
	mat4 model;
	vec3 colour;
};
uniform	CRE_RendEnt entities[10];
*/
void main() {
	//CRE_RendEnt current = entities[gl_DrawID];
	aColour = colour2;

	gl_Position = CRE_world * vec4(aPosition,1);
}