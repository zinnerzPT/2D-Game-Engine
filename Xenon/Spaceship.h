#pragma once
#include "Pawn.h"
#include <string>

class Spaceship : public Pawn
{
public:
	Spaceship(std::string filePath, int x, int y);
	void update(float deltaTime);
};

