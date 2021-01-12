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
	virtual void update(float deltaTime) override = 0;
	virtual void onContact(ContactSensor* otherSensor = nullptr) override = 0;
	virtual void takeDamage(float damage);
	virtual ~Enemy();

protected:
	float health = 100.0f;
	Tilemap* tilemap = nullptr;
	Animation* animation = nullptr;
};