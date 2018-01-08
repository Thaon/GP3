#ifndef CAMPH_H
#define CAMPH_H

#include "Model.h"

class CameraPlaceholder : public Model
{
public:

	bool m_cam1Active = false;

	Model* m_player;

	void Start() override;

	void Update(float deltaTime) override;

	void OnCollision(Model* collider) override;

private:
};

#endif