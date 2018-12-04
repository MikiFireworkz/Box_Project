#pragma once
#include "Box_Project.hpp"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = -45.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Constructor 
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH)
		: front_(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed_(SPEED), mouseSensitivity_(SENSITIVTY), zoom_(ZOOM)
	{
		position_ = position;
		worldUp_ = up;
		yaw_ = yaw;
		pitch_ = pitch;
		updateCameraVectors();
	}
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
		: front_(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed_(SPEED), mouseSensitivity_(SENSITIVTY), zoom_(ZOOM)
	{
		position_ = glm::vec3(posX, posY, posZ);
		worldUp_ = glm::vec3(upX, upY, upZ);
		yaw_ = yaw;
		pitch_ = pitch;
		updateCameraVectors();
	}

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(position_, position_ + front_, up_);
	}

	GLfloat GetZoom()
	{
		return zoom_;
	}

	glm::vec3 GetPosition()
	{
		return position_;
	}

	void PosUpdate(InputProcessor *inputProcessor, GLfloat deltaTime)
	{
		// Camera controls

		if (inputProcessor->keys(GLFW_KEY_W) || inputProcessor->keys(GLFW_KEY_UP))
		{
			processKeyboard(FORWARD, deltaTime);
		}

		if (inputProcessor->keys(GLFW_KEY_S) || inputProcessor->keys(GLFW_KEY_DOWN))
		{
			processKeyboard(BACKWARD, deltaTime);
		}

		if (inputProcessor->keys(GLFW_KEY_A) || inputProcessor->keys(GLFW_KEY_LEFT))
		{
			processKeyboard(LEFT, deltaTime);
		}

		if (inputProcessor->keys(GLFW_KEY_D) || inputProcessor->keys(GLFW_KEY_RIGHT))
		{
			processKeyboard(RIGHT, deltaTime);
		}
	}
	void ViewAngleUpdate(InputProcessor *inputProcessor)
	{
		ProcessMouseMovement(inputProcessor->xOffset(), inputProcessor->yOffset());
		inputProcessor->xOffset(0);
		inputProcessor->yOffset(0);
	}

private:
	glm::vec3 position_;
	glm::vec3 front_;
	glm::vec3 up_;
	glm::vec3 right_;
	glm::vec3 worldUp_;

	GLfloat yaw_;
	GLfloat pitch_;

	GLfloat movementSpeed_;
	GLfloat mouseSensitivity_;
	GLfloat zoom_;

	void updateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
		front.y = sin(glm::radians(pitch_));
		front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
		front_ = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		right_ = glm::normalize(glm::cross(front_, worldUp_));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		up_ = glm::normalize(glm::cross(right_, front_));
	}
	void processKeyboard(Camera_Movement direction, GLfloat deltaTime)
	{
		GLfloat distance = this->movementSpeed_ * deltaTime;

		if (direction == FORWARD)
		{
			position_ += front_ * distance;
		}
		if (direction == BACKWARD)
		{
			position_ -= front_ * distance;
		}
		if (direction == LEFT)
		{
			position_ -= right_ * distance;
		}
		if (direction == RIGHT)
		{
			position_ += right_ * distance;
		}
	}
	void processMouseScroll(GLfloat yOffset)
	{

	}
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true)
	{
		xOffset *= mouseSensitivity_;
		yOffset *= mouseSensitivity_;

		yaw_ += xOffset;
		pitch_ += yOffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (pitch_ > 89.0f)
			{
				pitch_ = 89.0f;
			}

			if (this->pitch_ < -89.0f)
			{
				this->pitch_ = -89.0f;
			}
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		this->updateCameraVectors();
	}

};