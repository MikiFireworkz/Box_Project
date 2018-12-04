#pragma once
#include "Box_Project.hpp"

class World
{
public:
	// Factory Method
	static World *CreateWorld(GLFWwindow *window){ return new World(window); }

	// Acsessor
	inline Camera camera() const { return camera_; }
	inline int screenWidth() const { return screenWidth_; }
	inline int screenHeight() const { return screenHeight_; }
	
	~World()
	{
		delete[] objects_;
		delete[] directionalLights_;
		delete[] spotLights_;
		delete[] pointLights_;
	}

	void RotateObject(GLint index, glm::vec3 rotate)
	{
		objects_[index].Rotate += rotate;
	}

	GLboolean CreateObject(Shader* shader, Mesh* mesh, Texture* texture, glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f) )
	{
		if (numActiveObjects_ < MAX_OBJECTS)
		{
			objects_[numActiveObjects_].ObjectShader = shader;
			objects_[numActiveObjects_].ObjectMesh = mesh;
			objects_[numActiveObjects_].ObjectTexture = texture;

			objects_[numActiveObjects_].Move = position;
			objects_[numActiveObjects_].Rotate = rotate;
			objects_[numActiveObjects_].Scale = scale;

			numActiveObjects_++;

			return GL_TRUE;
		}
		return GL_FALSE;
	}
	GLboolean DeleteObject(const unsigned int index)
	{
		if (numActiveObjects_ >= index)
		{
			numActiveObjects_--;

			Object tmp = objects_[numActiveObjects_];
			objects_[numActiveObjects_] = objects_[index];
			objects_[index] = tmp;

			return GL_TRUE;
		}

		return GL_FALSE;
	}

	GLboolean CreateDirectionalLight()
	{
		if (numActiveDirectionalLights_ < MAX_DIRECTIONAL_LIGHTS)
		{
			numActiveDirectionalLights_++;
		}
	}
	GLboolean DeleteDirectionalLight()
	{
		if (numActiveDirectionalLights_ > 0)
		{
			numActiveDirectionalLights_--;
		}
	}

	GLboolean CreateSpotLight()
	{
		if (numActiveSpotLights_ < MAX_SPOT_LIGHTS)
		{
			numActiveSpotLights_++;
		}
	}
	GLboolean DeleteSpotLight()
	{
		if (numActiveSpotLights_ > 0)
		{
			numActiveSpotLights_--;
		}
	}

	GLboolean CreatePointLight()
	{
		if (numActivePointLights_ < MAX_POINT_LIGHTS)
		{
			numActivePointLights_++;
		}
	}
	GLboolean DeletePointLight()
	{
		if (numActivePointLights_ > 0)
		{
			numActivePointLights_--;
		}
	}

	void Init()
	{
		//Create Resources
		Shader *shader = ResourceManeger::CreateShader("res\\shaders\\object.vert", "res\\shaders\\object.frag");
		Mesh *mesh = ResourceManeger::CreateMesh("res\\mesh\\box.csv");
		Texture *texture1 = ResourceManeger::CreateTexture("res\\texture\\orange.jpg");
		Texture *texture2 = ResourceManeger::CreateTexture("res\\texture\\cloud.png");
		Texture *texture3 = ResourceManeger::CreateTexture("res\\texture\\kzl9so6jm8dz.jpg");
		// Create Object
		CreateObject(shader, mesh, texture1);
		CreateObject(shader, mesh, texture2, glm::vec3(15.0f, 0.0f, 0.0f), glm::vec3(45.0f, 0.0f, 0.0f), glm::vec3(5.0f, 10.0f, 15.0f));
		CreateObject(shader, mesh, texture3, glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(45.0f, 45.0f, 45.0f), glm::vec3(5.0f, 5.0f, 5.0f));
		
		time_.Start();
	}
	// Loop Functions
	void Update(InputProcessor *inputProcessor)
	{
		time_.UpdataTime();

		RotateObject(0, glm::vec3(0.0f, 0.0f, time_.deltaTime() / 7.0f));
		RotateObject(1, glm::vec3(0.0f, 0.0f, time_.deltaTime() / 5.0f));
		RotateObject(2, glm::vec3(0.0f, 0.0f, time_.deltaTime() / 3.0f));

		camera_.PosUpdate(inputProcessor, time_.deltaTime());
		camera_.ViewAngleUpdate(inputProcessor);
	}
	void Render()
	{
		for (unsigned int i = 0; i < numActiveObjects_; i++)
		{
			objects_[i].ObjectShader->On();
			objects_[i].ObjectMesh->On();
			SetUniforms(i);
			glDrawArrays(GL_TRIANGLES, 0, objects_[i].ObjectMesh->GetVerticesCount());
			objects_[i].ObjectMesh->Off();
			objects_[i].ObjectShader->Off();
		}
	}

private:
	World(GLFWwindow *window)
		:camera_(Camera(glm::vec3(0.0f, 20.0f, 20.0f)))
	{
		SetScreenSize(window);
		objects_ = new Object[MAX_OBJECTS];
		directionalLights_ = new DirectionalLight[MAX_DIRECTIONAL_LIGHTS];
		spotLights_ = new SpotLight[MAX_SPOT_LIGHTS];
		pointLights_ = new PointLight[MAX_POINT_LIGHTS];
	}

	Camera camera_;
	Time time_;
	int screenWidth_, screenHeight_;
	// Objects
	Object* objects_;
	const unsigned int MAX_OBJECTS = 16;
	unsigned int numActiveObjects_ = 0;

	// Lights
	DirectionalLight* directionalLights_;
	SpotLight* spotLights_;
	PointLight* pointLights_;
	const unsigned int MAX_DIRECTIONAL_LIGHTS = 4;
	const unsigned int MAX_SPOT_LIGHTS = 4;
	const unsigned int MAX_POINT_LIGHTS = 4;
	unsigned int numActiveDirectionalLights_ = 0;
	unsigned int numActiveSpotLights_ = 0;
	unsigned int numActivePointLights_ = 0;

	//BackGround backGround;
	//GLfloat time;
	//Gizumo gizumo;
	//Ground ground;

	void SetUniforms(unsigned int index)
	{
		glm::mat4 model = objects_[index].GetModelMatrix();
		glm::mat4 view = camera_.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera_.GetZoom(), (float)screenWidth_ / (float)screenHeight_, 0.01f, 1000.0f);

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(objects_[index].ObjectShader->Program, "model");
		GLint viewLoc = glGetUniformLocation(objects_[index].ObjectShader->Program, "view");
		GLint projLoc = glGetUniformLocation(objects_[index].ObjectShader->Program, "projection");
		GLint textLoc = glGetUniformLocation(objects_[index].ObjectShader->Program, "Texture");

		// Pass the matrices to the shader
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(projection));

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0 + objects_[index].ObjectTexture->Index);
		glBindTexture(GL_TEXTURE_2D, objects_[index].ObjectTexture->TextureId);
		glUniform1i(textLoc, objects_[index].ObjectTexture->Index);
	}
	void SetScreenSize(GLFWwindow* window)
	{
		int screenWidth, screenHeight;
		glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
		screenWidth_ = screenWidth;
		screenHeight_ = screenHeight;
		glViewport(0, 0, screenWidth_, screenHeight_);
	}

};