#pragma once
#include "Pawn.h"
#include <string>

#include "Tilemap.h"
#include "Animation.h"

class Spaceship : public Pawn
{
public:
	Spaceship(float x, float y);
	void update(float deltaTime);
	void fire();

private:
	Tilemap* tilemap;
	Animation* animation;
};

