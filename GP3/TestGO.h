#pragma once

#include "Model.h"

class TestGO : public Model
{
public:

	void Start() override
	{
		std::cout << "Called Start!" << std::endl;
		Audio::LoadSound("MenuMusic", "res/menu.wav");
		Audio::PlaySound("MenuMusic", true);
		GetTransform().SetScale(glm::vec3(0.2, 0.2, 0.2));

		for (auto mesh : meshes)
		{
			for (auto vert : mesh.vertices)
			{
				std::cout << vert.texCoord.x << " - " << vert.texCoord.y << std::endl;
			}
		}
	}

	void Update(float deltaTime) override
	{
		if (Input::KeyPressed(SDL_SCANCODE_SPACE))
			GetTransform().Rotate(45 * deltaTime, glm::vec3(0, 1, 0));
	}

	void OnCollision(Model* collider) override
	{

	}


private:


};