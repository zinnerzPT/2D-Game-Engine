#pragma once

#include "Actor.h"
#include "ContactSensor.h"
#include "Tilemap.h"
#include "Animation.h"

enum class VelocityDirection
{
	positive,
	negative
};

class Enemy : 
	public Actor,
	public ContactSensor
{
public:
	Enemy();
	virtual void update(float deltaTime) override;
	virtual void onContact(ContactSensor* otherSensor = nullptr) override;
	virtual void takeDamage(float damage);
	virtual ~Enemy();

protected:
	float health = 100.0f;
	float attackDamage = 0.0f;
	float velocity[2]{ 0.0f, 0.0f };
	int points = 1500;
};