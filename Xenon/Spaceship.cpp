#include "Spaceship.h"
#include "Input.h"

#include "Animation.h"
#include "Missile.h"

Spaceship::Spaceship(float x, float y) :Pawn(x, y)
{
	Texture* texture = new Texture("../graphics/Ship1.bmp");
	textures.push_back(texture);

	tilemap = new Tilemap(texture, 1, 7);
	tilemap->ChangeFrame(3);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,5,4,3,2,1 }, true);
	animation->play();
	xpos = x;
	ypos = y;
	moveSpeed = 200.0f;

	// Initialize values to use when creating a missile
	missileHalfSize[0] = missileHalfSize[1] = 8.0f / 16.0f;
	missileVelocity[0] = 0.0f;
	missileVelocity[1] = -20.0f;
}

void Spaceship::update(float deltaTime) 
{
	// Movement input
	if (Input::getInstance()->getKey("Right"))
	{
		moveRight(moveSpeed * deltaTime);
	}
	else if (Input::getInstance()->getKey("Left"))
	{
		moveRight(-moveSpeed * deltaTime);
	}

	if ((Input::getInstance()->getKeyDown("Space")))
	{
		fire();
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
		}
	*/

	Pawn::update(deltaTime);
}

void Spaceship::fire() 
{
	//Fire missiles
	float missilePosition[2]{ (xpos + 32) / 16.0f, ypos / 16.0f };
	new Missile(missilePosition, missileHalfSize, 1.0f, missileVelocity);
}
