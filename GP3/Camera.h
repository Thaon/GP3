#pragma once

#include "Common.h"

/***
	The Camera class provides a rough and minimal way to set and control the projection in the OpenGl application.
	
	To be noted that the camera position is passed to Shaders as a Uniform.
*/

struct Camera
{
public:
	Camera() {}

	void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	inline void SetPosition(glm::vec3 pos) { this->pos = pos; }

	glm::vec3 GetPosition() const { return this->pos; }

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};


