#version 450 core
#extension GL_ARB_bindless_texture : require
out vec4 imagery;
in vec2 uv;

layout(bindless_sampler) uniform sampler2DArray tex;
uniform int layer;
void main(){
	imagery = texture(tex,vec3(uv,layer));
}