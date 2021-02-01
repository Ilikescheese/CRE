#version 450 core
layout(location=0) in vec3 aPosition;
layout(location=1) in vec3 aNormals;
layout(location=2) in vec2 aUv;

out vec2 uv;

uniform mat4 CRE_proj,CRE_view,CRE_model;

void main() {
	uv = aUv;
	gl_Position = CRE_proj * CRE_view * CRE_model * vec4(aPosition,1);
}