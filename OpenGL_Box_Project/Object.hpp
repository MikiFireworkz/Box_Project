#pragma once

#include <GL\glew.h>

// Object Components
#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"

// GLM Mathemtics
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\rotate_vector.hpp"

class Object {
public:
	// Object Attributes
	glm::vec3 Move;
	glm::vec3 Rotate;
	glm::vec3 Scale;

	//Object Componets
	Shader* ObjectShader;
	Mesh* ObjectMesh;
	Texture* ObjectTexture;

	glm::mat4 GetModelMatrix()
	{
		//
		glm::mat4 model;
		glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

		yAxis = glm::rotate(yAxis, Rotate.x, xAxis);
		zAxis = glm::rotate(zAxis, Rotate.x, xAxis);
		zAxis = glm::rotate(zAxis, Rotate.y, yAxis);
		//Set axises
		//xAxis = glm::rotate(xAxis, Rotate.y, yAxis);
		//xAxis = glm::rotate(xAxis, Rotate.z, zAxis);
		//yAxis = glm::rotate(yAxis, Rotate.z, zAxis);

		model = glm::translate(model, Move);
		model = glm::rotate(model, Rotate.z, zAxis);
		model = glm::rotate(model, Rotate.y, yAxis);
		model = glm::rotate(model, Rotate.x, xAxis);
		model = glm::scale(model, Scale);

		// Get the model matrix
		return model;
	}

private:
};

