#version 450 core
layout(location=0) in vec3 aPosition;
layout(location=1) in vec3 aNormals;
layout(location=2) in vec2 aUv;

out vec2 uv;

layout(std140) uniform CRE_common {
	mat4 CRE_proj,CRE_view;
};

uniform mat4 CRE_model;
void main() {
	//Remove rotations
	mat4 modelView = CRE_view * CRE_model;

	modelView[0][0] = 1;
	modelView[0][1] = 0;
	modelView[0][2] = 0;

	modelView[1][0] = 0;
	modelView[1][1] = 1;
	modelView[1][2] = 0;

	modelView[2][0] = 0;
	modelView[2][1] = 0;
	modelView[2][2] = 1;
	uv = aUv;
	gl_Position = CRE_proj * modelView * vec4(aPosition,1);
}