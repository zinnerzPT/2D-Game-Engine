#include "Spaceship.h"
#include <iostream>

Spaceship::Spaceship(float x, float y) :Pawn(x, y) {
	texture = new Texture("../graphics/Ship1.bmp");
	tilemap = new Tilemap(texture, 1, 7);
	tilemap->ChangeFrame(3);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,5,4,3,2,1 }, true);
	xpos = x;
	ypos = y;
}

void Spaceship::update(float deltaTime) {
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

	Pawn::update(deltaTime);
}

void Spaceship::fire() {
	//Fire missiles
}
