#pragma once
#include <vector>

#include "Actor.h"

class Level
{
	std::vector<Actor*> actors;
public:
	Level();
	void add(Actor* actor);
	void update(float deltaTime);
	class b2World* getWorld() { return world; };
	~Level();

private:
	struct b2Vec2* gravity;
	class b2World* world;
};

