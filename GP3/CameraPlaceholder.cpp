#include "CameraPlaceholder.h"

#include "SceneManager.h"

void CameraPlaceholder::Start()
{
	m_player = SceneManager::GetActiveScene()->GetModel("Player");
}

void CameraPlaceholder::Update(float deltaTime)
{
	GetTransform().SetPos(*m_player->GetTransform().GetPos() + glm::vec3(0, 5, -15));
}

void CameraPlaceholder::OnCollision(Model * collider)
{
}
