#pragma once

#include <vector>

#include "Tilemap.h"

class Animation
{
public:
	Animation(Tilemap* tilemap, std::vector<int> frames);
	void Draw();
	void SetLoop(bool value);

private:
	int numberOfFrames = 0;
	int currentFrame = 1;

	bool isLooping = true;

	std::vector<int> animationFrames;
	Tilemap* animationTilemap;

};