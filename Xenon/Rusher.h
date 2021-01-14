#pragma once
#include "Enemy.h"

class Rusher : public Enemy
{
public:
	Rusher(float x, float y, VelocityDirection velocityDirection = VelocityDirection::positive);
	void update(float deltaTime);
	void onContact(ContactSensor* otherSensor = nullptr) override;
	~Rusher();

private:
	// velocity at which the rusher moves
	float rusherVelocity = 8.0f;
};

