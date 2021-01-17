#pragma once

#include <list>
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
	struct Sound* loadSoundFile(const char* filepath);
	void playSound(struct Sound* sound);

	void updateBodies();
	void updateActors();
	void updateAnimations();
	void updateCanvases();

	class b2World* getWorld() { return world; };
	~Level();

private:
	std::list<Actor*> actors;
	std::list<Animation*> animations;
	std::list<UICanvas*> canvases;
	class b2World* world;

	class std::list<b2Body*> bodiesToEnable;
	class std::list<b2Body*> bodiesToDisable;

	std::list<Actor*> actorsToAdd;
	std::list<Animation*> animationsToAdd;
	std::list<Actor*> actorsToRemove;
	std::list<Animation*> animationsToRemove;
	std::list<UICanvas*> canvasesToAdd;
	std::list<UICanvas*> canvasesToRemove;

	struct AudioDevice* device;
	struct AudioContext* context;
	class OpenALWrapper* alWrapper;

	struct std::vector<Sound*> sounds;
};

