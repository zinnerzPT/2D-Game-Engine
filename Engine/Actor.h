#pragma once

#include "Texture.h"
#include <string>

class Actor
{
public:
	Actor();
	//~Actor();

	virtual void update(float deltaTime) = 0;
	void render();

protected:
	float xpos;
	float ypos;

	Texture* texture;

	SDL_Rect srcRect, destRect;

	int textureWidth, textureHeight;
	int frameWidth, frameHeight;
};
