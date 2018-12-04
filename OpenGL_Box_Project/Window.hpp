#pragma once

// Std. Includes
#include <iostream>
#include <cmath>

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "InputProcessor.hpp"

class Window
{
public:
	Window(const char* title)
	{

	}
private:
	InputProcessor inputProcessor;
};
