#pragma once
#include "Actor.h"
#include "ContactSensor.h"
#include "Spaceship.h"

class PowerUp :
	public Actor,
	public ContactSensor
{
public:
	PowerUp();
	virtual void update(float deltaTime) override;
	virtual void onContact(ContactSensor* otherSensor = nullptr) override = 0;
	virtual void applyPower(Spaceship* spaceship = nullptr) = 0;
	virtual ~PowerUp();

protected:
	float velocity[2]{ 0.0f, 2.0f };
};

