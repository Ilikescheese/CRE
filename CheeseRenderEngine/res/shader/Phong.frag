#version 460 core
#extension GL_ARB_bindless_texture : require
out vec4 imagery;
in vec2 uv;

//Phong lighting
in vec3 fragPos;
in vec3 normal;
uniform vec3 CRE_ambientColour = {1,1,1};
uniform vec3 CRE_lightColour = {1,1,1};
uniform vec3 CRE_viewPos;
uniform vec3 CRE_lightPos;

//Atlas Img
layout(bindless_sampler) uniform sampler2DArray CRE_texAtlas;

//Texture locating
struct TextureLocator {
	int layer;
	vec2 atlasSize;
	vec4 uvOffset; // the first two elements are the x and y offset. The 3rd and 
					// fourth elements are for zooming in. The offsets are given in pixels
};

//RendEnt
struct CRE_RendEnt {
	mat4 model;
	int layer;
	vec2 atlasSize;
	vec4 uvOffset; // the first two elements are the x and y offset. The 3rd and 
					// fourth elements are for zooming in. The offsets are given in pixels
	//TextureLocator texLoc;
};

uniform CRE_common {
	mat4 CRE_world;
	CRE_RendEnt entities[10];
};

void main(){
	CRE_RendEnt current = entities[gl_DrawId];

	//Ambient
	vec3 ambient = 0.1 * CRE_lightColour;
	//Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(CRE_lightPos - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * CRE_lightColour;
	//Specular
    vec3 viewDir = normalize(CRE_viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = 0.5 * spec * CRE_lightColour;

	//Scaling the texture
	vec2 scaled = uv * (current.uvOffset.zw / current.atlasSize) + (current.uvOffset.xy / current.atlasSize);
	imagery = vec4((ambient + diffuse + specular) * vec3(texture(CRE_texAtlas,vec3(scaled,current.layer))),1);
}