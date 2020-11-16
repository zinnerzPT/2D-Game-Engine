#pragma once

#include <vector>

#include "Tilemap.h"

class Animation
{
public:
	Animation(Tilemap* tilemap, std::vector<int> frames, bool loop);
	void update();

private:
	int numberOfFrames = 0;
	int currentFrame = 0;

	bool isLooping = true;

	std::vector<int> animationFrames;
	Tilemap* animationTilemap;

};