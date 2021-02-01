#version 450 core
#extension GL_ARB_bindless_texture : require
out vec4 imagery;
in vec2 uv;

//Atlas Img
layout(bindless_sampler) uniform sampler2DArray CRE_texAtlas;

//Texture locating
uniform vec2 CRE_atlasSize;
uniform int CRE_layer;
uniform vec4 CRE_uvOffset = {1,1,1,1}; // the first two elements are the x and y offset. The 3rd and 
									// fourth elements are for zooming in. The offsets are given in pixels

void main(){
	vec2 scaled = uv * (CRE_uvOffset.zw / CRE_atlasSize) + (CRE_uvOffset.xy / CRE_atlasSize);
	imagery = texture(CRE_texAtlas,vec3(scaled,CRE_layer));
	if(imagery.a < .1)
		discard;
}