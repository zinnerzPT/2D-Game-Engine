#include "Spaceship.h"
#include "Input.h"
#include "Animation.h"
#include "GameController.h"
#include "PowerUp.h"
#include "CompanionPowerUp.h"
#include "GameManager.h"

#include <chrono>

// DEBUG PURPOSES ONLY
#include <iostream>

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
	burnerTexRight->setTexOffset(32, 64);
	burnerTilemapRight = new Tilemap(burnerTexRight, 1, 2);
	burnerAnimRight = new Animation(burnerTilemapRight, { 0,1 }, true);
	burnerAnimRight->play();

	burnerTexLeft = new Texture("../graphics/Burner1.bmp");
	textures.push_back(burnerTexLeft);
	burnerTexLeft->setTexOffset(18, 64);
	burnerTilemapLeft = new Tilemap(burnerTexLeft, 1, 2);
	burnerAnimLeft = new Animation(burnerTilemapLeft, { 0,1 }, true);
	burnerAnimLeft->play();

	// Turning animations
	moveRightAnim = new Animation(tilemap, { 3,4,5,6 }, false);
	returnRightAnim = new Animation(tilemap, { 6,5,4,3 }, false);
	moveLeftAnim = new Animation(tilemap, { 3,2,1,0 }, false);
	returnLeftAnim = new Animation(tilemap, { 0,1,2,3 }, false);

	// Create rigidbody
	rigidBody->makeDynamic(1.0f);
	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	// The player uses category 1 and collides with categories 2(enemy), 4(enemy missile), 5(power up) and 6(companion)
	rigidBody->setCollisionFilter(CATEGORY_1, CATEGORY_2 | CATEGORY_4 | CATEGORY_5 | CATEGORY_6);
	rigidBody->createBody(position, halfSize);

	// Initialize spaceship movement speed
	moveSpeed = 600.0f;

	// Initialize values to use when creating a missile
	missileHalfSize[0] = missileHalfSize[1] = 8.0f / 16.0f;
	missileVelocity[0] = 0.0f;
	missileVelocity[1] = -40.0f;

	// Start thread that manages firing cooldown
	cooldownThread = std::thread{ &Spaceship::cooldownCheck, this };
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
	else
	{
		// Reset velocity in x
		velocity[0] = 0.0f;
		rigidBody->setVelocity(velocity);
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

	// Game controller movement
	if (controller->getIsDetected())
	{
		float leftAxisX = controller->getXAxis();
		float leftAxisY = controller->getYAxis();

		if (leftAxisX > 0.3f || leftAxisX < -0.3f)
		{
			moveRight(moveSpeed * deltaTime * leftAxisX);
		}
		if (leftAxisY > 0.3f || leftAxisY < -0.3f)
		{
			moveUp(moveSpeed * deltaTime * -leftAxisY);
		}
	}

	// Animation
	if (velocity[0] > 0.0f)
	{
		animateMoveRight();
	}
	else if (velocity[0] < 0.0f)
	{
		animateMoveLeft();
	}
	else
	{
		animateReturnRight();
		animateReturnLeft();
	}


	// Fire input
	if ((Input::getInstance()->getKey("Space")))
	{
		fire();
	}

	if (controller->getIsDetected())
	{
		if (controller->getButtonA())
		{
			fire();
		}
	}

	// Update companions
	if (companionToAttach)
	{
		float offset[2]{ 0.0f, 0.0f };
		if (companionToAttach == attachedCompanions[0])
		{
			offset[0] = 5.0f;
			offset[1] = -0.5f;
		}
		if (companionToAttach == attachedCompanions[1])
		{
			offset[0] = -5.0f;
			offset[1] = -0.5f;
		}
		float position[2]{ getPosition()[0] + offset[0], getPosition()[1] + offset[1] };
		companionToAttach->setPosition(position);
		companionToAttach = nullptr;
	}

	for (CompanionPowerUp* companion : attachedCompanions)
	{
		if (companion)
		{
			companion->setVelocity(velocity);
		}
	}

	Pawn::update(deltaTime);
}


void Spaceship::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	PowerUp* powerUp = nullptr;
	powerUp = dynamic_cast <PowerUp*> (otherSensor);
	if (powerUp)
	{
		powerUp->applyPower(this);
	}
}

Spaceship::~Spaceship()
{
	isAlive = false;
	if (cooldownThread.joinable())
	{
		cooldownThread.join();
	}
	GameManager::getInstance()->loseLife();
}

void Spaceship::fire()
{
	if (canFire)
	{
		canFire = false;
		// Fire missiles
		float missilePosition[2]{ (xpos + 32) / 16.0f, ypos / 16.0f };
		// Missile uses category 3 and collides with category 2(enemy)
		new Missile(missilePosition, missileHalfSize, 1.0f, missileVelocity, CATEGORY_3, CATEGORY_2, missileType);

		// Fire additional missile for each companion
		for (CompanionPowerUp* companion : attachedCompanions)
		{
			if (companion)
			{
				missilePosition[0] = companion->getPosition()[0];
				missilePosition[1] = companion->getPosition()[1];
				new Missile(missilePosition, missileHalfSize, 1.0f, missileVelocity, CATEGORY_3, CATEGORY_2, companion->getMissileType());
			}
		}
		needsCooldown = true;
	}
}

void Spaceship::addHealth(float additionalHealth)
{
	if (health + additionalHealth <= maxHealth)
	{
		health += additionalHealth;
	}
	else
	{
		health = maxHealth;
	}
	std::cout << "Spaceship HP: " << health << std::endl;
}


void Spaceship::takeDamage(float damage)
{
	if (health - damage > 0)
	{
		health -= damage;
	}
	else
	{
		health = 0;
		for (CompanionPowerUp* companion : attachedCompanions)
		{
			companion->destroy();
		}
		Actor::destroy();
	}
	std::cout << "Spaceship HP: " << health << std::endl;
}

void Spaceship::upgradeMissile()
{
	switch (missileType)
	{
	case MissileType::light:
		missileType = MissileType::medium;
		break;
	case MissileType::medium:
		missileType = MissileType::heavy;
		break;
	case MissileType::heavy:
		break;
	}
}

void Spaceship::attachCompanion(CompanionPowerUp* companion)
{
	if (!attachedCompanions[0])
	{
		attachedCompanions[0] = companion;
		companionToAttach = companion;
	}
	else if (!attachedCompanions[1])
	{
		attachedCompanions[1] = companion;
		companionToAttach = companion;
	}
}

void Spaceship::removeCompanion(class CompanionPowerUp* companion)
{
	if (this->attachedCompanions[0] == companion)
	{
		this->attachedCompanions[0] = nullptr;
	}
	if (this->attachedCompanions[1] == companion)
	{
		this->attachedCompanions[1] = nullptr;
	}
}

float* Spaceship::getPosition()
{
	return 	rigidBody->getPosition();
}

void Spaceship::cooldownCheck()
{
	while (isAlive)
	{
		if (needsCooldown)
		{
			needsCooldown = false;
			std::this_thread::sleep_for(std::chrono::milliseconds{ cooldown });
			canFire = true;
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds{ 10 });
		}
	}
}

void Spaceship::stopTurningAnims()
{
	moveRightAnim->stop();
	moveLeftAnim->stop();
	returnRightAnim->stop();
	returnLeftAnim->stop();
}

void Spaceship::animateMoveRight()
{
	if (!isMovingRight)
	{
		isMovingRight = true;
		isMovingLeft = false;
		stopTurningAnims();
		moveRightAnim->playFromStart();
	}
}

void Spaceship::animateMoveLeft()
{
	if (!isMovingLeft)
	{
		isMovingLeft = true;
		isMovingRight = false;
		stopTurningAnims();
		moveLeftAnim->playFromStart();
	}
}

void Spaceship::animateReturnRight()
{
	if (isMovingRight)
	{
		isMovingRight = false;
		stopTurningAnims();
		returnRightAnim->playFromStart();
	}
}

void Spaceship::animateReturnLeft()
{
	if (isMovingLeft)
	{
		isMovingLeft = false;
		stopTurningAnims();
		returnLeftAnim->playFromStart();
	}
}

