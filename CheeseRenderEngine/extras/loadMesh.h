#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Mesh.h"
#include "Logger.h"
#include "glWrapper/VertConfig.h"

//*******************load the first mesh of an object
chre::Mesh loadMesh(const char *path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	if (!scene)
	{
		Logger::err("Model loading failure from path:", path);
		return chre::Mesh();
	}
	chre::Mesh result;
	const aiMesh *current = nullptr;

	for (int curMesh = 0; curMesh < scene->mNumMeshes; ++curMesh) {
		current = scene->mMeshes[curMesh];


		for (int curFace = 0; curFace < current->mNumFaces; curFace++)
		{
			aiFace &face = current->mFaces[curFace];
			for (int i = 0; i < face.mNumIndices; ++i)
				result.indices.push_back(face.mIndices[i]);
		}


		for (int i = 0; i < current->mNumVertices; i++)
		{
			//Position
			result.vertices.push_back(current->mVertices[i].x);
			result.vertices.push_back(current->mVertices[i].y);
			result.vertices.push_back(current->mVertices[i].z);

			//Normals
			result.vertices.push_back(current->mNormals[i].x);
			result.vertices.push_back(current->mNormals[i].y);
			result.vertices.push_back(current->mNormals[i].z);

			//Tex coords
			if (current->mTextureCoords[0])
			{
				result.vertices.push_back(current->mTextureCoords[0][i].x);
				result.vertices.push_back(current->mTextureCoords[0][i].y);
			}
		}
	}
	return result;
}
