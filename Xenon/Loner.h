#pragma once
#include "Enemy.h"
class Loner : public Enemy
{
public:
	Loner();
	virtual void update(float deltaTime) override;
	~Loner();
};

