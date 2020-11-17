#pragma once

#include "Enemy.h"

class Loner : public Enemy
{
public:
	Loner(float x, float y);
	void update(float deltaTime);
	~Loner();
};

