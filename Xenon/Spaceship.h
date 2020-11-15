#pragma once
#include "Pawn.h"
#include <string>

class Spaceship : public Pawn
{
public:
	Spaceship(std::string filePath, Renderer* renderer, int x, int y);
	void update(float deltaTime);
};

