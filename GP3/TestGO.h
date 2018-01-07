#pragma once

#include "Model.h"

class TestGO : public Model
{
public:

	float m_speed = 50;

	void Start() override
	{
		std::cout << "Called Start!" << std::endl;
		Audio::LoadSound("MenuMusic", "res/menu.wav");
		Audio::PlaySound("MenuMusic", true);
		//GetTransform().SetScale(glm::vec3(0.2, 0.2, 0.2));
	}

	void Update(float deltaTime) override
	{
		if (Input::KeyPressed(SDL_SCANCODE_RIGHT))
			GetTransform().Move(glm::vec3(m_speed * deltaTime, 0, 0));

		if (Input::KeyPressed(SDL_SCANCODE_LEFT))
			GetTransform().Move(glm::vec3(-m_speed * deltaTime, 0, 0));

		if (Input::KeyPressed(SDL_SCANCODE_UP))
			GetTransform().Move(glm::vec3(0, 0, m_speed * deltaTime));

		if (Input::KeyPressed(SDL_SCANCODE_DOWN))
			GetTransform().Move(glm::vec3(0, 0, -m_speed * deltaTime));
	}

	void OnCollision(Model* collider) override
	{
		std::cout << "Collided with " << collider->GetName() << std::endl;
	}


private:


};