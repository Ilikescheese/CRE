#version 450 core
#extension GL_ARB_separate_shader_objects : require
//Output blocks such as these are necessary vert shaders due to the need for a stricter interface when dealing with modular shaders
out gl_PerVertex { vec4 gl_Position; };

layout(location=0) in vec3 position;
layout(location=2) in vec2 uvs;

uniform mat4 proj,view,model;
out vec2 uv;

void main() {
	uv = uvs;
	gl_Position = proj * view * model * vec4(position,1);
}