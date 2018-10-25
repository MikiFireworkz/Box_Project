#pragma once

#include <GL\glew.h>

// GLM Mathemtics
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

class DirectionalLight
{
public:
	DirectionalLight()
	{

	}
private:
	glm::vec3 direction;
};

class SpotLight
{
public:
	SpotLight()
	{

	}
private:
	glm::vec3 position;
	glm::vec3 direction;
};

class PointLight
{
public:
	PointLight()
	{

	}
private:
	glm::vec3 position;
};