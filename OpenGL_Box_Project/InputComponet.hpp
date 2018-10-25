#pragma once

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "World.hpp"

// GLM Mathemtics
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

class InputComponent
{
public:

	// Moves/alters the camera positions based on user input
	void DoCameraMovement(Camera& camera, GLfloat deltaTime)
	{
		// Camera controls
		if (keys_[GLFW_KEY_W] || keys_[GLFW_KEY_UP])
		{
			camera.ProcessKeyboard(FORWARD, deltaTime);
		}

		if (keys_[GLFW_KEY_S] || keys_[GLFW_KEY_DOWN])
		{
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		}

		if (keys_[GLFW_KEY_A] || keys_[GLFW_KEY_LEFT])
		{
			camera.ProcessKeyboard(LEFT, deltaTime);
		}

		if (keys_[GLFW_KEY_D] || keys_[GLFW_KEY_RIGHT])
		{
			camera.ProcessKeyboard(RIGHT, deltaTime);
		}
	}

	// Is called whenever a key is pressed/released via GLFW
	void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
	{
		if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if (key >= 0 && key < 1024)
		{
			if (action == GLFW_PRESS)
			{
				keys_[key] = true;
			}
			else if (action == GLFW_RELEASE)
			{
				keys_[key] = false;
			}
		}
	}

	void MouseCallback(GLFWwindow *window, double xPos, double yPos)
	{
		if (firstMouse_)
		{
			lastX_ = xPos;
			lastY_ = yPos;
			firstMouse_ = false;
		}

		xOffset_ = xPos - lastX_;
		yOffset_ = lastY_ - yPos;  // Reversed since y-coordinates go from bottom to left

		lastX_ = xPos;
		lastY_ = yPos;

		//world.camera.ProcessMouseMovement(xOffset, yOffset);
	}

private:
	GLfloat xOffset_, yOffset_;

	bool keys_[1024];
	GLfloat lastX_ = 400, lastY_ = 300;
	bool firstMouse_ = true;
};