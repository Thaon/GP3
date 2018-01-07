#pragma once

#include "Common.h"

#include "Display.h"
#include "SceneManager.h"

/***
	The MainGame class acts as a hub between all the systems and handles them, enabling the game to be initialized, configured and run.
*/

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void InitDisplay(int width, int height, glm::vec4 clearColour);
	void run();
	void SetActiveCamera(Camera* camera);

private:

	void initSystems();
	void processInput(float delta);
	void CalculateCollisions();
	void gameLoop();
	void drawGame(float delta);

	Display* m_gameDisplay;
	Camera* m_activeCam;
	GameState m_gameState;

	float oldTime, m_burnAmount, newTime;
	bool m_burning = false;

	glm::vec4 m_backgroundColour;
};

