#pragma once
#include "Box_Project.hpp"

// Function prototypes
inline void Initialize();
inline void Update(World *world, InputProcessor *inputProcessor);
inline void Render(World *world, GLFWwindow *window);
inline void OptionSet();
inline void Terminate();


int main()
{
	Initialize();

	InputProcessor *inputProcessor = nullptr;
	GLFWwindow *window = WindowManeger::CreateWindow(1200, 900, "OpenGL_Box", inputProcessor);
	World *world = World::CreateWorld(window);
	world->Init();
	OptionSet();
	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		Update(world, inputProcessor);
		Render(world, window);
	}

	Terminate();
	return 0;
}

inline void Initialize() {
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow *tempWindow = glfwCreateWindow(1200, 900, "OpenGL_Box", nullptr, nullptr);

	if (nullptr == tempWindow)
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		glfwTerminate();

		return exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(tempWindow);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return exit(EXIT_FAILURE);
	}

	glfwDestroyWindow(tempWindow);
}
inline void OptionSet()
{
	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT); 

	//アルファブレンディング注意！！
	// enable alpha support
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw in wireframe
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}
inline void Update(World *world, InputProcessor *inputProcessor)
{
	glfwPollEvents();
	world->Update(inputProcessor);
}
inline void Render(World *world, GLFWwindow *window)
{
	// Clear the colorbuffer
	glClearColor(0.05f, 0.05f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	world->Render();

	// Swap the buffers
	glfwSwapBuffers(window);
}
inline void Terminate()
{
	glfwTerminate();
}
