#pragma once
#include "Pawn.h"
#include <string>

class Spaceship : public Pawn
{
public:
	Spaceship(std::string filePath, float x, float y);
	void update(float deltaTime);
};

