#pragma once

#include "Enemy.h"

class Rusher : public Enemy
{
public:
	Rusher(float x, float y);
	void update(float deltaTime);
	void onContact(ContactSensor* otherSensor = nullptr) override;
	~Rusher();
};

