#pragma once

#include "RigidBody.h"
#include "ContactSensor.h"

class Projectile : public ContactSensor
{
public:
	Projectile(float position[2], float halfSize[2], float density, float linearVelocity[2]);

	virtual void onContact() override = 0;
};

