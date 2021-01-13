#pragma once
#include "Enemy.h"

class Drone : public Enemy
{
public:
	Drone(float x, float y, float delay = 0);
	void update(float deltaTime);
	void onContact(ContactSensor* otherSensor = nullptr) override;
	~Drone();

private:
	float moveDelay = 0;
	float frameTime = 0;
};

