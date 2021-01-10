#include "Spaceship.h"
#include "Input.h"

#include "Animation.h"

Spaceship::Spaceship(float x, float y) :Pawn(x, y) {
	Texture* texture = new Texture("../graphics/Ship1.bmp");
	textures.push_back(texture);

	tilemap = new Tilemap(texture, 1, 7);
	tilemap->ChangeFrame(3);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,5,4,3,2,1 }, true);
	animation->play();
	xpos = x;
	ypos = y;
	moveSpeed = 200.0f;
}

void Spaceship::update(float deltaTime) {

	if (Input::getInstance()->getKey("Right")) {
		moveRight(moveSpeed * deltaTime);
	}
	else if (Input::getInstance()->getKey("Left")) {
		moveRight(-moveSpeed * deltaTime);
	}
		/*
	keyState = SDL_GetKeyboardState(NULL);
if (keyState[SDL_SCANCODE_RIGHT]) {

	//moveRight(moveSpeed * deltaTime);
}
else if (keyState[SDL_SCANCODE_LEFT]) {
	//moveRight(-moveSpeed * deltaTime);
}
if (keyState[SDL_SCANCODE_DOWN]) {
	//moveUp(-moveSpeed * deltaTime);
}
else if (keyState[SDL_SCANCODE_UP]) {
	//moveUp(moveSpeed * deltaTime);
}

// Game controller movement
//float leftAxisX = controller->getXAxis();
//if (leftAxisX > 0.3f || leftAxisX < -0.3f)
{
	//moveRight(moveSpeed * deltaTime * leftAxisX);
}

//float leftAxisY = controller->getYAxis();
//if (leftAxisY > 0.3f || leftAxisY < -0.3f)
{
	//moveUp(moveSpeed * deltaTime * -leftAxisY);
}*/

	Pawn::update(deltaTime);
}

void Spaceship::fire() {
	//Fire missiles
}
