#include "Spaceship.h"
#include "Input.h"

#include "Animation.h"
#include "Missile.h"

Spaceship::Spaceship(float x, float y) :Pawn(x, y)
{
	// Spaceship tilemap
	Texture* texture = new Texture("../graphics/Ship1.bmp");
	textures.push_back(texture);

	tilemap = new Tilemap(texture, 1, 7);
	tilemap->ChangeFrame(3);

	// Spaceship burners
	burnerTexRight = new Texture("../graphics/Burner1.bmp");
	textures.push_back(burnerTexRight);
	burnerTexRight->setTexOffset( 32, 64);
	burnerTilemapRight = new Tilemap(burnerTexRight, 1, 2);
	burnerAnimRight = new Animation(burnerTilemapRight, { 0,1 }, true);
	burnerAnimRight->play();

	burnerTexLeft = new Texture("../graphics/Burner1.bmp");
	textures.push_back(burnerTexLeft);
	burnerTexLeft->setTexOffset( 18, 64);
	burnerTilemapLeft = new Tilemap(burnerTexLeft, 1, 2);
	burnerAnimLeft = new Animation(burnerTilemapLeft, { 0,1 }, true);
	burnerAnimLeft->play();

	// Turning animations
	moveRightAnim = new Animation(tilemap, { 3,4,5,6 }, false);
	returnRightAnim = new Animation(tilemap, { 6,5,4,3 }, false);
	moveLeftAnim = new Animation(tilemap, { 3,2,1,0 }, false);
	returnLeftAnim = new Animation(tilemap, { 0,1,2,3 }, false);

	// Create rigidbody
	rigidBody = new RigidBody();
	rigidBody->makeDynamic(1.0f);
	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	rigidBody->setCollisionFilter(CATEGORY_1, CATEGORY_4);
	rigidBody->createBody(position, halfSize);

	// Initialize spaceship movement speed
	moveSpeed = 600.0f;

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

		// Moving right animation
		if (!isMovingRight)
		{
			isMovingRight = true;
			isMovingLeft = false;
			stopTurningAnims();
			moveRightAnim->playFromStart();
		}
	}
	else if (Input::getInstance()->getKey("Left"))
	{
		moveRight(-moveSpeed * deltaTime);

		// Moving left animation
		if (!isMovingLeft)
		{
			isMovingLeft = true;
			isMovingRight = false;
			stopTurningAnims();
			moveLeftAnim->playFromStart();
		}
	}
	else
	{
		// Reset velocity in x
		velocity[0] = 0.0f;
		rigidBody->setVelocity(velocity);

		// Return right animation
		if (isMovingRight)
		{
			isMovingRight = false;
			stopTurningAnims();
			returnRightAnim->playFromStart();
		}
		// Return left animation
		if (isMovingLeft)
		{
			isMovingLeft = false;
			stopTurningAnims();
			returnLeftAnim->playFromStart();
		}
	}

	if (Input::getInstance()->getKey("Up"))
	{
		moveUp(moveSpeed * deltaTime);
	}
	else if (Input::getInstance()->getKey("Down"))
	{
		moveUp(-moveSpeed * deltaTime);
	}
	else
	{
		// Reset velocity in y
		velocity[1] = 0.0f;
		rigidBody->setVelocity(velocity);
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
	new Missile(missilePosition, missileHalfSize, 1.0f, missileVelocity, CATEGORY_3, CATEGORY_2);
}

void Spaceship::stopTurningAnims()
{
	moveRightAnim->stop();
	moveLeftAnim->stop();
	returnRightAnim->stop();
	returnLeftAnim->stop();
}

