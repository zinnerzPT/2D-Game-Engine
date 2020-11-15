#pragma once

#include "Texture.h"
#include "Renderer.h"
#include <string>

class Actor
{
public:
	//Actor(std::string textureFilePath, Renderer renderer);
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
