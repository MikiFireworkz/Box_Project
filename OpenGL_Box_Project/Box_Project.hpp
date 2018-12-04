#pragma once

#define DEBUG_CODE(str) std::cout << str << std::endl

// Std. Includes
#include <iostream>
#include <cmath>

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathemtics
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

// Classes

#include "InputProcessor.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Object.hpp"
#include "ResourceManeger.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Time.hpp"
#include "WindowManeger.hpp"

#include "Camera.hpp"
#include "World.hpp"