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

	void addBodyToDestroy(class b2Body* b);
	void addBodyToEnable(class b2Body* b);
	void addBodyToDisable(class b2Body* b);

	void addActorToRemove(Actor* actor);
	void addAnimationToRemove(Animation* animation);

	void update(float deltaTime);
	void render();
	void animate();

	void updateBodies();
	void removeActors();
	void removeAnimations();

	class b2World* getWorld() { return world; };
	~Level();

private:
	std::vector<Actor*> actors;
	std::vector<Animation*> animations;
	struct b2Vec2* gravity;
	class b2World* world;

	class std::vector<b2Body*> bodiesToDestroy;
	class std::vector<b2Body*> bodiesToEnable;
	class std::vector<b2Body*> bodiesToDisable;

	std::vector<Actor*> actorsToRemove;
	std::vector<Animation*> animationsToRemove;
};

