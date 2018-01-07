#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


MainGame::MainGame()
{
	m_activeCam = nullptr;
	m_gameState = GameState::PLAY;
	m_gameDisplay = nullptr;
	m_backgroundColour = glm::vec4(0, 0, 0, 0);
}

MainGame::~MainGame()
{
	delete m_gameDisplay;
}

void MainGame::InitDisplay(int width, int height, glm::vec4 clearColour)
{
	m_gameDisplay = new Display(width, height);
	m_gameDisplay->initDisplay();
	m_backgroundColour = clearColour;
}

void MainGame::run()
{
	initSystems();
	gameLoop();
}

void MainGame::SetActiveCamera(Camera* camera)
{
	m_activeCam = camera;
}

void MainGame::initSystems()
{
	oldTime = newTime = m_burnAmount = 0;

	//initialize input
	Input::Init();

	//and audio
	Audio::Init();

	//call Start on all objects in the scene
	for (auto model : SceneManager::GetActiveScene()->GetModels())
	{
		model->Start();
	}
}

void MainGame::gameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		oldTime = newTime;
		newTime = SDL_GetPerformanceCounter();
		float deltaTime = (newTime - oldTime) / SDL_GetPerformanceFrequency() / 100; //milliseconds
		//std::cout << "old: " << oldTime << std::endl << "new: " << newTime << std::endl << "delta: " << deltaTime << std::endl;

		processInput(deltaTime);

		CalculateCollisions();

		//call Update on all objects in the scene
		for (auto model : SceneManager::GetActiveScene()->GetModels())
		{
			if (model->m_isCamera)
			{
				m_activeCam->SetPosition(*model->GetTransform().GetPos());
				//m_activeCam->SetRotation(model->GetTransform().GetRot()->x, model->GetTransform().GetRot()->y, model->GetTransform().GetRot()->z);
				//std::cout << m_activeCam->GetPosition().x << " - " << m_activeCam->GetPosition().y << " - " << m_activeCam->GetPosition().z << std::endl;

			}
			if (model->GetName() == "Player")
			{
				m_activeCam->LookAt(*model->GetTransform().GetPos());
			}

			model->Update(deltaTime);
		}

		drawGame(deltaTime);
	}
}

void MainGame::processInput(float delta)
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				m_gameState = GameState::EXIT;
				break;

			case SDL_KEYDOWN:
				/* Check the SDLKey values and move change the coords */
				switch (evnt.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					m_gameState = GameState::EXIT;
					break;
				}
				Input::m_keyStates[evnt.key.keysym.scancode] = true;
				break;
			case SDL_KEYUP:
				Input::m_keyStates[evnt.key.keysym.scancode] = false;
				break;
		}
	}
	
	if (m_burning)
	{
		if (m_burnAmount < 1)
			m_burnAmount += .5f * delta;
	}
	else
	{
		if (m_burnAmount > 0)
			m_burnAmount -= .5f * delta;
	}
}

void MainGame::CalculateCollisions()
{
	for (int i = 0; i < SceneManager::GetActiveScene()->GetModels().size() - 1; i++)
	{
		for (int j = 1; j < SceneManager::GetActiveScene()->GetModels().size(); j++)
		{
			//cache models and check if they can collide
			Model* md1 = SceneManager::GetActiveScene()->GetModels().at(i);
			Model* md2 = SceneManager::GetActiveScene()->GetModels().at(j);

			if (md1->CanCollide() && md2->CanCollide())
			{
				//calculate distances and check for collision, if so, notify both objects that the collision happened
				float dis = glm::distance(*md1->GetTransform().GetPos(), *md2->GetTransform().GetPos()); //need to dereference the Transform component
				if (dis < md1->GetColliderRadius() || dis < md2->GetColliderRadius())
				{
					md1->OnCollision(md2);
					md2->OnCollision(md1);
				}
			}
		}
	}
}

Transform transform;
void MainGame::drawGame(float delta)
{
	m_gameDisplay->clearDisplay(m_backgroundColour.r, m_backgroundColour.g, m_backgroundColour.b, m_backgroundColour.a);

	for (auto model : SceneManager::GetActiveScene()->GetModels())
	{
		//bind shader
		model->GetShader()->Bind();
		model->GetTransform().Update();
		model->GetShader()->Update(model->GetTransform(), *m_activeCam, delta, m_burnAmount);
		
		//textures are bound in the Mesh's draw function

		//draw
		model->Draw(*model->GetShader());
	}
				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	m_gameDisplay->swapBuffer();
} 