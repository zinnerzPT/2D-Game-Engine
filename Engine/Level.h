#pragma once
#include <vector>

#include "Actor.h"

class Level
{
public:
	Level();
	void add(Actor* actor);
	void update(float deltaTime);
	class b2World* getWorld() { return world; };
	~Level();

private:
	std::vector<Actor*> actors;
	struct b2Vec2* gravity;
	class b2World* world;
};

