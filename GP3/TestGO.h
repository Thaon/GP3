#pragma once

#include "Model.h"

class TestGO : public Model
{
public:

	float m_speed = 3;
	float m_startingHeight = 0;
	float m_yVelocity = 0;
	bool m_jumping = false;
	glm::vec3 m_previousPos; //for collision resolution

	void Start() override
	{
		//std::cout << "Called Start!" << std::endl;
		Audio::LoadSound("MenuMusic", "res/menu.wav");
		//Audio::PlaySound("MenuMusic", true);
		//GetTransform().SetScale(glm::vec3(0.2, 0.2, 0.2));

		m_startingHeight = GetTransform().GetPos()->y;
	}

	void Update(float deltaTime) override
	{
		m_previousPos = *GetTransform().GetPos();

		if (Input::KeyPressed(SDL_SCANCODE_RIGHT))
			GetTransform().Move(glm::vec3(-m_speed * deltaTime, 0, 0));

		if (Input::KeyPressed(SDL_SCANCODE_LEFT))
			GetTransform().Move(glm::vec3(m_speed * deltaTime, 0, 0));

		if (Input::KeyPressed(SDL_SCANCODE_UP))
			GetTransform().Move(glm::vec3(0, 0, m_speed * deltaTime));

		if (Input::KeyPressed(SDL_SCANCODE_DOWN))
			GetTransform().Move(glm::vec3(0, 0, -m_speed * deltaTime));

		if (Input::KeyPressed(SDL_SCANCODE_SPACE))
		{
			if (GetTransform().GetPos()->y == m_startingHeight)
			{
				m_yVelocity = 10;
				m_jumping = true;
			}
		}

		//if in the air, add gravity
		if (GetTransform().GetPos()->y > m_startingHeight)
		{
			m_yVelocity -= 9.81 * deltaTime;
		}
		else
		{
			if (m_jumping && m_yVelocity < 0)
			{
				GetTransform().SetPos(glm::vec3(GetTransform().GetPos()->x, m_startingHeight, GetTransform().GetPos()->z));
				m_yVelocity = 0;
				m_jumping = false;
			}
		}

		//update object
		GetTransform().Move(glm::vec3(0, m_yVelocity * deltaTime, 0));
	}

	void OnCollision(Model* collider) override
	{
		GetTransform().SetPos(m_previousPos);
		//collider->Destroy();
	}


private:


};