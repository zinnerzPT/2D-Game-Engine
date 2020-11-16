#include "Pawn.h"
#include "Engine.h"
#include <iostream>

Pawn::Pawn(std::string filePath, float x, float y) {

	texture = new Texture(filePath);

	xpos = x;
	ypos = y;

	if (texture->getDstRect())
	{
		int frameWidth = texture->getDstRect()->w;
		int frameHeight = texture->getDstRect()->h;
	}
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

	//texture->getDstRect()->x = xpos;
	//texture->getDstRect()->y = ypos;
	//texture->getDstRect()->w = texture->getSrcRect()->w;
	//texture->getDstRect()->h = texture->getSrcRect()->h;
}

void Pawn::moveRight(float x) {
	xpos += x;
}

void Pawn::moveUp(float y) {
	ypos -= y;
}
