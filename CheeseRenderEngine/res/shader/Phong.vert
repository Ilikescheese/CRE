#version 460 core
layout(location=0) in vec3 aPosition;
layout(location=1) in vec3 aNormals;
layout(location=2) in vec2 aUv;

out vec2 uv;
//Phong lighting
out vec3 normal;
out vec3 fragPos;

//Texture locating
struct TextureLocator {
	int layer;
	vec2 atlasSize;
	vec4 uvOffset; // the first two elements are the x and y offset. The 3rd and 
					// fourth elements are for zooming in. The offsets are given in pixels
};

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

void main() {
	CRE_RendEnt current = entities[0];

	normal = mat3(transpose(inverse(current.model))) * aNormals;
	fragPos = vec3(current.model * vec4(aPosition,1));

	uv = aUv;
	gl_Position = CRE_world * current.model * vec4(fragPos,1);
}