#pragma once

#include "Common.h"
#include "camera.h"

/***
	The Transform class stores information about:
	-Position
	-Rotation
	-Scale
	for each Model in the scene

	Additionally it provides methods to operate on those variables and a getter for the Model Matrix to be passed to shaders	
*/

struct Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;

		modelMatrix = glm::mat4(1.0f);
		translationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::mat4(1.0f);
		scaleMatrix = glm::mat4(1.0f);
	}

	inline glm::mat4 GetModel() const
	{
		return modelMatrix;
	}

	inline void Update()
	{
		translationMatrix = glm::translate(pos);
		scaleMatrix = glm::scale(scale);

		modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	}

	inline glm::vec3* GetPos() { return &pos; } //getters
	inline glm::vec3* GetRot() { return &rot; }
	inline glm::vec3* GetScale() { return &scale; }

	inline void SetPos(glm::vec3& pos) { this->pos = pos; } // setters
	inline void SetScale(glm::vec3& scale) { this->scale = scale; }
	inline void SetRotation(glm::vec3 change)
	{
		rot = change;
		rotationMatrix = glm::eulerAngleXYZ(rot.x, rot.y, rot.z);
	}

	inline void Rotate(float amt, glm::vec3& axis)
	{ 
		rotationMatrix *= glm::rotate(glm::mat4(), amt, axis);
	}

protected:
private:
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 modelMatrix;

	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};


