#include "Pawn.h"
#include "Engine.h"
#include "Renderer.h"
#include <iostream>

Pawn::Pawn(std::string filePath, int x, int y) : Actor(x,y) {

	texture = new Texture(filePath);

	xpos = x;
	ypos = y;

	texture->query(&textureWidth, &textureHeight);

	frameWidth = textureWidth / 8;
	frameHeight = textureHeight / 2;

	srcRect.x = srcRect.y = 0;
	srcRect.w = frameWidth;
	srcRect.h = frameHeight;
}

Pawn::~Pawn()
{
	delete texture;
}

void Pawn::update(float deltaTime)
{
	//moveRight(1.0f);
	//moveUp(-1.0f);

	/*srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;*/

	

	const Uint8* keyState;
	keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_RIGHT]) {
		moveRight(100 * deltaTime);
	}
	else if (keyState[SDL_SCANCODE_LEFT]) {
		moveRight(-100 * deltaTime);
	}
	if (keyState[SDL_SCANCODE_DOWN]) {
		moveUp(-100 * deltaTime);
	}
	else if (keyState[SDL_SCANCODE_UP]) {
		moveUp(100 * deltaTime);
	}

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void Pawn::moveRight(float x) {
	xpos += x;
}

void Pawn::moveUp(float y) {
	ypos -= y;
}

void Pawn::render()
{
	Engine::renderer->copy(texture, &srcRect, &destRect);
}
