#include "Animation.h"
#include <iostream>

Animation::Animation(Tilemap* tilemap, std::vector<int> frames)
{
	animationTilemap = tilemap;
	numberOfFrames = frames.size();
	animationFrames = frames;
}

void Animation::Draw()
{
	animationTilemap->ChangeFrame(animationFrames[currentFrame - 1]);
	currentFrame++;
	if (currentFrame > numberOfFrames)
	{
		if (isLooping)
		{
			currentFrame = 1;
		}
		else
		{
			currentFrame--;
		}
	}
	// std::cout << "Current animation frame: " << currentFrame << std::endl;
}

void Animation::SetLoop(bool value)
{
	isLooping = value;
}
