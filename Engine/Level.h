#pragma once

#include <vector>
#include "Actor.h"
#include "Animation.h"
#include "UICanvas.h"

class Level
{
public:
	Level(float gravityX, float gravityY);
	void addActor(Actor* actor);
	void addAnimation(Animation* animation);
	void addCanvas(UICanvas* canvas);

	void addBodyToEnable(class b2Body* b);
	void addBodyToDisable(class b2Body* b);

	void addActorToRemove(Actor* actor);
	void addAnimationToRemove(Animation* animation);
	void addCanvasToRemove(UICanvas* canvas);

	void update(float deltaTime);
	void render();
	void animate();

	void updateBodies();
	void updateActors();
	void updateAnimations();
	void updateCanvases();

	class b2World* getWorld() { return world; };
	~Level();

private:
	std::vector<Actor*> actors;
	std::vector<Animation*> animations;
	std::vector<UICanvas*> canvases;
	struct b2Vec2* gravity;
	class b2World* world;

	class std::vector<b2Body*> bodiesToEnable;
	class std::vector<b2Body*> bodiesToDisable;

	std::vector<Actor*> actorsToAdd;
	std::vector<Animation*> animationsToAdd;
	std::vector<Actor*> actorsToRemove;
	std::vector<Animation*> animationsToRemove;
	std::vector<UICanvas*> canvasesToAdd;
	std::vector<UICanvas*> canvasesToRemove;
};

