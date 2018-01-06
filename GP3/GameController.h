#pragma once

#include "Common.h"

#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "transform.h"
#include "SceneManager.h"


/***
	this class will be the only access point to the engine to manipulate Models at every frame, alongside the main function, which can be used to set up initial data for them.

	A very rough ooutline of Unity's MonoBehavior was used as an inspiration for the class.
*/

class GameController
{
public:
	GameController();
	~GameController();

	void Start();
	void Update(float deltaTime);

private:
	float counter;
	Model* m1, *m2, *m3;
};

