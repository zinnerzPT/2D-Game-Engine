#pragma once
#include "Actor.h"
#include "ContactSensor.h"
#include "Spaceship.h"

class PowerUp :
	public Actor,
	public ContactSensor
{
public:
	virtual void update(float deltaTime) override = 0;
	virtual void onContact(ContactSensor* otherSensor = nullptr) override = 0;
	virtual void applyPower(Spaceship* spaceship = nullptr) = 0;
	virtual ~PowerUp();

protected:

};

