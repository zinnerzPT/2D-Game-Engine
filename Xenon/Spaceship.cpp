#include "Spaceship.h"

Spaceship::Spaceship(float x, float y) :Pawn(x, y) {
	texture = new Texture("../graphics/Ship1.bmp");
	tilemap = new Tilemap(texture, 1, 7);
	tilemap->ChangeFrame(3);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,5,4,3,2,1 }, true);
	xpos = x;
	ypos = y;
	moveSpeed = 200.0f;
	controller = new GameController();
}

void Spaceship::update(float deltaTime) {
	const Uint8* keyState;

	keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_RIGHT]) {
		moveRight(moveSpeed * deltaTime);
	}
	else if (keyState[SDL_SCANCODE_LEFT]) {
		moveRight(-moveSpeed * deltaTime);
	}
	if (keyState[SDL_SCANCODE_DOWN]) {
		moveUp(-moveSpeed * deltaTime);
	}
	else if (keyState[SDL_SCANCODE_UP]) {
		moveUp(moveSpeed * deltaTime);
	}

	//moveRight(controller->getXAxis()*deltaTime);
	//moveUp(-controller->getYAxis() * deltaTime);

	// Game controller movement
	float leftAxisX = controller->getXAxis();
	if (leftAxisX > 4000|| leftAxisX <-4000)
	{
		moveRight( moveSpeed * deltaTime * (leftAxisX / 32767.0f));
	}

	float leftAxisY = controller->getYAxis();
	if (leftAxisY > 4000 || leftAxisY < -4000)
	{
		moveUp(moveSpeed * deltaTime * -(leftAxisY / 32767.0f));
	}

	//std::cout << "x= "<< xpos << "y=" << ypos << std::endl;
	Pawn::update(deltaTime);
}

void Spaceship::fire() {
	//Fire missiles
}
