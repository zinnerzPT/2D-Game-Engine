#pragma once

#include "Pawn.h"

class Spaceship : public Pawn
{
public:
	Spaceship(float x, float y);
	void update(float deltaTime);
	void fire();
};

