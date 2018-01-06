#include "GameController.h"



GameController::GameController()
{
}


GameController::~GameController()
{
}

void GameController::Start()
{
	/*m1 = SceneManager::GetActiveScene()->GetModel("nanosuit");
	m1->GetTransform().SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	m1->GetTransform().SetPos(glm::vec3(0.0, -5.0, 20.0));
	m1->GetTransform().SetRotation(glm::vec3(0, 0, 0));

	m2 = SceneManager::GetActiveScene()->GetModel("monkey");
	m2->GetTransform().SetPos(glm::vec3(-3, 1.0, 0.0));
	m2->GetTransform().SetScale(glm::vec3(.8f, .8f, .8f));

	m3 = SceneManager::GetActiveScene()->GetModel("Alien");
	m3->GetTransform().SetPos(glm::vec3(3, 1.0, 0.0));
	m3->GetTransform().SetScale(glm::vec3(3, 3, 3));*/
}

void GameController::Update(float deltaTime)
{
	counter = 1;

	//m1->GetTransform().SetScale(glm::vec3(sinf(counter * deltaTime), sinf(counter * deltaTime), sinf(counter * deltaTime)));
	/*m1->GetTransform().Rotate(counter * deltaTime, glm::vec3(0, 1, 0));
	m2->GetTransform().Rotate(-counter * deltaTime, glm::vec3(0, 1, 0));
	m3->GetTransform().Rotate(counter * deltaTime, glm::vec3(0, 1, 0));*/

	/*m2->GetTransform().SetRot(glm::vec3(0.0, counter, 0.0));
	m3->GetTransform().SetRot(glm::vec3(0.0, counter, 0.0));*/
	//transform.SetPos(glm::vec3(sinf(counter), 0.0, 0.0));
}
