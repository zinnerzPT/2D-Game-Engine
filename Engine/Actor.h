#pragma once

#include "Texture.h"
#include "Renderer.h"
#include <string>

class Actor
{
public:
	Actor(int x, int y);
	//~Actor();

	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

protected:
	float xpos;
	float ypos;

	Texture* texture;

	SDL_Rect srcRect, destRect;
	Renderer* renderer;
};
