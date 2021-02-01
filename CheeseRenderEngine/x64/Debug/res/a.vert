#version 450 core
layout(location=0) in vec3 position;
layout(location=2) in vec2 uvs;

uniform mat4 proj,view,model;
out vec2 uv;

void main() {
	uv = uvs;
	gl_Position = proj * view * model * vec4(position,1);
}