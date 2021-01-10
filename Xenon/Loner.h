#pragma once

#include "Enemy.h"

class Loner : public Enemy
{
public:
	Loner(float x, float y);
	void update(float deltaTime);
	~Loner();

private:

	bool movementReversed = false;
	float velocity[2]{ 3.75f, 0.0f };
};

