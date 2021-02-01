#version 460 core
#extension GL_ARB_bindless_texture : require
out vec4 imagery;

in vec3 aColour;

void main(){
	imagery = vec4(vec3(aColour),1);
}