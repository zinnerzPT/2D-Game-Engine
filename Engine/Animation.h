#pragma once

#include <vector>
#include "Tilemap.h"
#include "Actor.h"

class Animation
{
public:
	Animation(Tilemap* tilemap, std::vector<int> frames, bool loop);

	void update();
	void play();
	void playFromStart();
	void stop();
	void destroyAfterEnd(Actor* actor);

	~Animation();

private:
	int numberOfFrames = 0;
	int currentFrame = 0;

	bool isLooping = true;
	bool isActive = false;

	std::vector<int> animationFrames;
	Tilemap* animationTilemap;
	Actor* actorToDestroy = nullptr;
};