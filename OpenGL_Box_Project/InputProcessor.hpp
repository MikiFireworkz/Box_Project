#pragma once
#include "Box_Project.hpp"

class InputProcessor
{
public:
	InputProcessor(GLFWwindow *window)
		: xOffset_(0), yOffset_(0)
	{
		// Keys ÇÃèâä˙âª
		for (int i = 0; i < 1024; i++)
		{
			keys_[i] = false;
		}
		
		// GLFWÇÃÉnÉìÉhÉãÇ…é©ï™é©êgÇìoò^
		glfwSetWindowUserPointer(window, this);
		// Set callback functions
		glfwSetKeyCallback(window, this->keyCallback);
		glfwSetCursorPosCallback(window, this->mousePosCallback);
		glfwSetMouseButtonCallback(window, this->mouseButtonCallback);
		glfwSetScrollCallback(window, this->scrollCallback);
	}

	GLfloat xOffset() { return xOffset_; }
	GLfloat yOffset() { return yOffset_; }
	bool keys(unsigned int key) { return keys_[key]; }

	void xOffset(GLfloat xOffset) { xOffset_ = xOffset; }
	void yOffset(GLfloat yOffset) { yOffset_ = yOffset; }

private:
	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
	{
		InputProcessor* inputProcessor = static_cast<InputProcessor*>(glfwGetWindowUserPointer(window));
		if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if (key >= 0 && key < 1024)
		{
			if (action == GLFW_PRESS)
			{
				inputProcessor->keys_[key] = true;
			}
			else if (action == GLFW_RELEASE)
			{
				inputProcessor->keys_[key] = false;
			}
		}
	}
	static void mousePosCallback(GLFWwindow *window, double xPos, double yPos)
	{
		InputProcessor* inputProcessor = static_cast<InputProcessor*>(glfwGetWindowUserPointer(window));
		if (inputProcessor->firstMouse_)
		{
			inputProcessor->lastX_ = xPos;
			inputProcessor->lastY_ = yPos;
			inputProcessor->firstMouse_ = false;
		}

		inputProcessor->xOffset_ += xPos - inputProcessor->lastX_;
		inputProcessor->yOffset_ += inputProcessor->lastY_ - yPos;

		inputProcessor->lastX_ = xPos;
		inputProcessor->lastY_ = yPos;
	}
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		DEBUG_CODE("Call mouseButtonCallback");
	}
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		DEBUG_CODE("Call scrollCallback");
	}

	GLfloat xOffset_, yOffset_;
	GLfloat lastX_, lastY_;
	bool keys_[1024];
	bool firstMouse_ = true;

	bool tempFlag = true;
};