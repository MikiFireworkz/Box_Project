#pragma once

// Std. Includes
#include <iostream>
#include <cmath>

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "InputProcessor.hpp"

class WindowManeger
{
public:
	static GLFWwindow *CreateWindow(int width, int height, const char* title, InputProcessor*& inputProcessor)
	{
		GLFWwindow *window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(window);

		inputProcessor = new InputProcessor(window);
		// Set Input Processors
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		return window;
	}

};