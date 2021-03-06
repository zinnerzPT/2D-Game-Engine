#pragma once
#include "Enemy.h"
#include "EnemyProjectile.h"

class Loner : public Enemy
{
public:
	Loner(float x, float y, VelocityDirection velocityDirection = VelocityDirection::positive);
	void update(float deltaTime);
	void onContact(ContactSensor* otherSensor = nullptr) override;
	~Loner();

private:
	void attack();

private:
	// velocity at which the loner moves
	float lonerVelocity = 5.0f;

	float attackDelay = 2.0f;
	float chargingAttack = 0.0f;
	float projectileHalfSize[2];
	float projectileVelocity[2];
};

