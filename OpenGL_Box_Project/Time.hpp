#pragma once

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

class Time
{
public:
	void Start()
	{
		latestTime_ = lastTime_ = glfwGetTime();
		isPaused_ = GL_FALSE;
	}
	void UpdataTime()
	{
		currentTime_ = glfwGetTime();
		if (!isPaused_){now_ = currentTime_ - latestTime_;}
		deltaTime_ = currentTime_ - lastTime_;
		lastTime_ = currentTime_;
	}
	void Pause()
	{
		if (!isPaused_)
		{
			isPaused_ = GL_TRUE;
			pausedAt_ = currentTime_;
		}
	}
	void Resume()
	{
		if (isPaused_)
		{
			isPaused_ = GL_FALSE;
			latestTime_ += currentTime_ - pausedAt_;
		}
	}

	const GLfloat now() const
	{
		return now_;
	}
	const GLfloat deltaTime() const
	{
		return deltaTime_;
	}

private:
	
	GLfloat now_; // Startしてから何フレーム経過したか
	GLfloat deltaTime_; // UpdateTime毎のフレーム間隔

	GLfloat latestTime_;
	GLfloat lastTime_;
	GLfloat currentTime_;
	GLfloat pausedAt_;
	GLboolean isPaused_;
};