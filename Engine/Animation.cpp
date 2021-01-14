#include "Animation.h"
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
	if (isActive)
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
				currentFrame = 0;
				isActive = false;
			}

			if (actorToDestroy != nullptr)
			{
				actorToDestroy->destroy();
				actorToDestroy = nullptr;
			}
		}
	}
}

void Animation::play()
{
	isActive = true;
}

void Animation::playFromStart()
{
	currentFrame = 0;
	isActive = true;
}

void Animation::stop()
{
	isActive = false;
}

void Animation::destroyAfterEnd(Actor* actor)
{
	actorToDestroy = actor;
}

Animation::~Animation()
{
	isActive = false;
	Engine::getLevel()->addAnimationToRemove(this);
}

