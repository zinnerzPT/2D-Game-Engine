#pragma once
#include <vector>

#include "Actor.h"

class Level
{
	std::vector<Actor*> actors;
public:
	void add(Actor* actor);
	void update(float deltaTime);
	~Level();
};

