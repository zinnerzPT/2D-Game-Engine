#pragma once

#include "Actor.h"
#include "ContactSensor.h"
#include "Tilemap.h"
#include "Animation.h"

class Enemy : 
	public Actor,
	public ContactSensor
{
public:
	Enemy();
	virtual void update(float deltaTime) override = 0;
	virtual void onContact(ContactSensor* otherSensor = nullptr) override;
	virtual void takeDamage(float damage);
	virtual ~Enemy();

protected:
	float health = 100.0f;
	float attackDamage = 0.0f;
	float velocity[2]{ 0.0f, 0.0f };
};