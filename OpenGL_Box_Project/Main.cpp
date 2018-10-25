// Std. Includes
#include <iostream>
#include <cmath>

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "World.hpp"
#include "Time.hpp"

// GLM Mathemtics
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#define DEBUG_CODE(str) std::cout << str << std::endl

// Properties
const GLuint WIDTH = 1200, HEIGHT = 900;

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoCameraMovement();
void Updata();
void Render(GLFWwindow *window);

bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

Time time;

// Create World
World world;

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL_Box", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &world.screenWidth, &world.screenHeight);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, world.screenWidth, world.screenHeight);

	//Define Components
	Shader shader("res\\shaders\\object.vert", "res\\shaders\\object.frag");
	Mesh mesh("res\\mesh\\box.csv");
	Texture texture1("res\\texture\\image2.png");
	Texture texture2("res\\texture\\cloud.png");
	// Create Object
	world.CreateObject(&shader, &mesh, &texture1);
	world.CreateObject(&shader, &mesh, &texture2, glm::vec3(15.0f, 0.0f, 0.0f), glm::vec3(45.0f, 0.0f, 0.0f), glm::vec3(5.0f, 10.0f, 15.0f));
	world.CreateObject(&shader, &mesh, &texture1, glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(45.0f, 45.0f, 45.0f), glm::vec3(5.0f, 5.0f, 5.0f));

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

	time.Start();
	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Update time
		time.UpdataTime();

		// Check and call events
		glfwPollEvents();
		DoCameraMovement();

		// Updata
		//Updata(window);
		world.RotateObject(0, glm::vec3(0.0f, 0.0f, time.deltaTime() / 5.0f));
		world.RotateObject(1, glm::vec3(0.0f, 0.0f, time.deltaTime() / 5.0f));
		world.RotateObject(2, glm::vec3(0.0f, 0.0f, time.deltaTime() / 5.0f));
		// Render
		Render(window);
	}

	glfwTerminate();
	return 0;
}

void Updata(GLFWwindow *window)
{/* （仮）
	// Update time
	time.UpdataTime();

	// Check and call events
	glfwPollEvents();
	InputUpdata();

	DoCameraMovement();
*/}

void Render(GLFWwindow *window)
{
	// Clear the colorbuffer
	glClearColor(0.05f, 0.05f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	world.Render();

	// Swap the buffers
	glfwSwapBuffers(window);
}

// Moves/alters the camera positions based on user input
void DoCameraMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		world.camera.ProcessKeyboard(FORWARD, time.deltaTime());
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		world.camera.ProcessKeyboard(BACKWARD, time.deltaTime());
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		world.camera.ProcessKeyboard(LEFT, time.deltaTime());
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		world.camera.ProcessKeyboard(RIGHT, time.deltaTime());
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
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	world.camera.ProcessMouseMovement(xOffset, yOffset);
}