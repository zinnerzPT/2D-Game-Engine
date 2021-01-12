#pragma once

#include "Actor.h"
#include "ContactSensor.h"

class Pawn : 
	public Actor,
	public ContactSensor
{
public:
	Pawn(float x, float y);
	void update(float deltaTime);
	void moveRight(float x);
	void moveUp(float y);

	virtual void onContact(ContactSensor* otherSensor = nullptr) override = 0;
	~Pawn();

protected:
	float moveSpeed;
	float velocity[2]{ 0.0f, 0.0f };
	class GameController* controller;
};

