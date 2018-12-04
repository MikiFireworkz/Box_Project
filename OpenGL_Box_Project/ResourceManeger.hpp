#pragma once
#include "Box_Project.hpp"

class ResourceManeger
{
public:
	// Factory Method
	static Shader *CreateShader(const GLchar *vertexPath, const GLchar *fragmentPath)
	{
		return new Shader(vertexPath, fragmentPath);
	}
	static Texture *CreateTexture(const GLchar *texturePath)
	{
		return new Texture(texturePath);
	}
	static Mesh *CreateMesh(const GLchar *verticesPath)
	{
		return new Mesh(verticesPath);
	}
private:

};