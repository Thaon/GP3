#ifndef CAMPH_H
#define CAMPH_H

#include "Model.h"

class CameraPlaceholder : public Model
{
public:

	Model* m_player;

	void Start() override;

	void Update(float deltaTime) override;

	void OnCollision(Model* collider) override;

private:
};

#endif