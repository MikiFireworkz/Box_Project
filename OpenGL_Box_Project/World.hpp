#pragma once

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// World Components
#include "Object.hpp"
#include "Camera.hpp"
#include "Light.hpp"

// GLM Mathemtics
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

class World
{
public:
	// Camera
	Camera camera;
	int screenWidth, screenHeight;

	World()
		:camera(Camera(glm::vec3(0.0f, 20.0f, 20.0f)))
	{
		objects = new Object[MAX_OBJECTS];
		directionalLights = new DirectionalLight[MAX_DIRECTIONAL_LIGHTS];
		spotLights = new SpotLight[MAX_SPOT_LIGHTS];
		pointLights = new PointLight[MAX_POINT_LIGHTS];
	}
	~World()
	{
		delete[] objects;
		delete[] directionalLights;
		delete[] spotLights;
		delete[] pointLights;
	}

	void RotateObject(GLint index, glm::vec3 rotate)
	{
		objects[index].Rotate += rotate;
	}

	GLboolean CreateObject(Shader* shader, Mesh* mesh, Texture* texture, glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f) )
	{
		if (numActiveObjects < MAX_OBJECTS)
		{
			objects[numActiveObjects].ObjectShader = shader;
			objects[numActiveObjects].ObjectMesh = mesh;
			objects[numActiveObjects].ObjectTexture = texture;

			objects[numActiveObjects].Move = position;
			objects[numActiveObjects].Rotate = rotate;
			objects[numActiveObjects].Scale = scale;

			numActiveObjects++;

			return GL_TRUE;
		}
		return GL_FALSE;
	}
	GLboolean DeleteObject(const unsigned int index)
	{
		if (numActiveObjects >= index)
		{
			numActiveObjects--;

			Object tmp = objects[numActiveObjects];
			objects[numActiveObjects] = objects[index];
			objects[index] = tmp;

			return GL_TRUE;
		}

		return GL_FALSE;
	}

	GLboolean CreateDirectionalLight()
	{
		if (numActiveDirectionalLights < MAX_DIRECTIONAL_LIGHTS)
		{
			numActiveDirectionalLights++;
		}
	}
	GLboolean DeleteDirectionalLight()
	{
		if (numActiveDirectionalLights > 0)
		{
			numActiveDirectionalLights--;
		}
	}

	GLboolean CreateSpotLight()
	{
		if (numActiveSpotLights < MAX_SPOT_LIGHTS)
		{
			numActiveSpotLights++;
		}
	}
	GLboolean DeleteSpotLight()
	{
		if (numActiveSpotLights > 0)
		{
			numActiveSpotLights--;
		}
	}

	GLboolean CreatePointLight()
	{
		if (numActivePointLights < MAX_POINT_LIGHTS)
		{
			numActivePointLights++;
		}
	}
	GLboolean DeletePointLight()
	{
		if (numActivePointLights > 0)
		{
			numActivePointLights--;
		}
	}

	void Render()
	{
		for (unsigned int i = 0; i < numActiveObjects; i++)
		{
			objects[i].ObjectShader->On();
			objects[i].ObjectMesh->On();
			SetUniforms(i);
			glDrawArrays(GL_TRIANGLES, 0, objects[i].ObjectMesh->GetVerticesCount());
			objects[i].ObjectMesh->Off();
			objects[i].ObjectShader->Off();
		}
	}

private:
	// Objects
	Object* objects;
	const unsigned int MAX_OBJECTS = 16;
	unsigned int numActiveObjects = 0;

	// Camera
	//Camera camera;

	// Lights
	DirectionalLight* directionalLights;
	SpotLight* spotLights;
	PointLight* pointLights;
	const unsigned int MAX_DIRECTIONAL_LIGHTS = 4;
	const unsigned int MAX_SPOT_LIGHTS = 4;
	const unsigned int MAX_POINT_LIGHTS = 4;
	unsigned int numActiveDirectionalLights = 0;
	unsigned int numActiveSpotLights = 0;
	unsigned int numActivePointLights = 0;

	//BackGround backGround;
	//GLfloat time;
	//Gizumo gizumo;
	//Ground ground;

	void SetUniforms(unsigned int index)
	{
		glm::mat4 model = objects[index].GetModelMatrix();
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)screenWidth / (float)screenHeight, 0.01f, 1000.0f);

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(objects[index].ObjectShader->Program, "model");
		GLint viewLoc = glGetUniformLocation(objects[index].ObjectShader->Program, "view");
		GLint projLoc = glGetUniformLocation(objects[index].ObjectShader->Program, "projection");
		GLint textLoc = glGetUniformLocation(objects[index].ObjectShader->Program, "Texture");

		// Pass the matrices to the shader
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(projection));

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0 + objects[index].ObjectTexture->Index);
		glBindTexture(GL_TEXTURE_2D, objects[index].ObjectTexture->TextureId);
		glUniform1i(textLoc, objects[index].ObjectTexture->Index);
	}

};