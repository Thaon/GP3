#include "CameraPlaceholder.h"

#include "SceneManager.h"

void CameraPlaceholder::Start()
{
	m_player = SceneManager::GetActiveScene()->GetModel("Player");
}

void CameraPlaceholder::Update(float deltaTime)
{
	if (!m_cam1Active)
		GetTransform().SetPos(*m_player->GetTransform().GetPos() + glm::vec3(0, 15, -15));
	else
		GetTransform().SetPos(*m_player->GetTransform().GetPos() + glm::vec3(-10, 15, -5));

	if (Input::KeyPressed(SDL_SCANCODE_1))
		m_cam1Active = false;

	if (Input::KeyPressed(SDL_SCANCODE_2))
		m_cam1Active = true;
}

void CameraPlaceholder::OnCollision(Model * collider)
{
}
