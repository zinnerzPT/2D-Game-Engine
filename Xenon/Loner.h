#pragma once
#include "Enemy.h"

class Loner : public Enemy
{
public:
	Loner(float x, float y);
	void update(float deltaTime);
	void onContact(ContactSensor* otherSensor = nullptr) override;
	~Loner();

private:
	bool movementReversed = false;
	float velocity[2]{ 5.0f, 0.0f };
};

