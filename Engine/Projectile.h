#pragma once

#include "RigidBody.h"

class Projectile
{
public:
	Projectile(float position[2], float halfSize[2], float linearVelocity[2]);

	virtual void onCollision() = 0;

	~Projectile();

private:
	RigidBody rigidBody;
};

