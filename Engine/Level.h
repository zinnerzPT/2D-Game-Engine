#pragma once

#include <vector>
#include "Actor.h"
#include "Animation.h"

class Level
{
public:
	Level();
	void addActor(Actor* actor);
	void addAnimation(Animation* animation);
	void update(float deltaTime);
	void render();
	void animate();
	class b2World* getWorld() { return world; };
	~Level();

private:
	std::vector<Actor*> actors;
	std::vector<Animation*> animations;
	struct b2Vec2* gravity;
	class b2World* world;
};

