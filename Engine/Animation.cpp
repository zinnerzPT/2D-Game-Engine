#include "Animation.h"
#include <iostream>
#include "Engine.h"
#include "Level.h"

Animation::Animation(Tilemap* tilemap, std::vector<int> frames, bool loop)
{
	isLooping = loop;
	animationTilemap = tilemap;
	numberOfFrames = frames.size();
	animationFrames = frames;

	Engine::getLevel()->addAnimation(this);
}

void Animation::update()
{
	animationTilemap->ChangeFrame(animationFrames[currentFrame]);
	++currentFrame;
	if (currentFrame >= numberOfFrames)
	{
		if (isLooping)
		{
			currentFrame = 0;
		}
		else
		{
			currentFrame--;
		}
	}
	// std::cout << "Current animation frame: " << currentFrame << std::endl;
}

