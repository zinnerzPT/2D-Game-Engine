#pragma once

#include "Actor.h"
#include <string>

class Background :
	public Actor
{
public:
	Background(std::string filepath);
	void update(float deltaTime);
};

