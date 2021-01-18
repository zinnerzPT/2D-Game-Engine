#include "Spaceship.h"
#include "Input.h"
#include "Animation.h"
//#include "GameController.h"
#include "PowerUp.h"
#include "CompanionPowerUp.h"
#include "GameManager.h"

#include "Engine.h"
#include "Level.h"

#include <chrono>

Spaceship::Spaceship(float x, float y) :Pawn(x, y)
{
	// Spaceship tilemap
	Texture* texture = new Texture("../graphics/Ship1.bmp");
	textures.push_back(texture);

	Tilemap* tilemap = new Tilemap(texture, 1, 7);
	tilemaps.push_back(tilemap);
	tilemap->ChangeFrame(3);

	// Spaceship burners
	burnerTexRight = new Texture("../graphics/Burner1.bmp");
	textures.push_back(burnerTexRight);
	burnerTexRight->setTexOffset(32, 64);
	burnerTilemapRight = new Tilemap(burnerTexRight, 1, 2);
	tilemaps.push_back(burnerTilemapRight);
	burnerAnimRight = new Animation(burnerTilemapRight, { 0,1 }, true);
	animations.push_back(burnerAnimRight);
	burnerAnimRight->play();

	burnerTexLeft = new Texture("../graphics/Burner1.bmp");
	textures.push_back(burnerTexLeft);
	burnerTexLeft->setTexOffset(18, 64);
	burnerTilemapLeft = new Tilemap(burnerTexLeft, 1, 2);
	tilemaps.push_back(burnerTilemapLeft);
	burnerAnimLeft = new Animation(burnerTilemapLeft, { 0,1 }, true);
	animations.push_back(burnerAnimLeft);
	burnerAnimLeft->play();

	// Turning animations
	moveRightAnim = new Animation(tilemap, { 3,4,5,6 }, false);
	animations.push_back(moveRightAnim);
	returnRightAnim = new Animation(tilemap, { 6,5,4,3 }, false);
	animations.push_back(returnRightAnim);
	moveLeftAnim = new Animation(tilemap, { 3,2,1,0 }, false);
	animations.push_back(moveLeftAnim);
	returnLeftAnim = new Animation(tilemap, { 0,1,2,3 }, false);
	animations.push_back(returnLeftAnim);

	// Create rigidbody
	rigidBody->makeDynamic(1.0f);
	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	// The player uses category 1 and collides with categories 2(enemy), 4(enemy missile), 5(power up) and 6(companion)
	rigidBody->setCollisionFilter(CATEGORY_1, CATEGORY_2 | CATEGORY_4 | CATEGORY_5 | CATEGORY_6);
	rigidBody->createBody(position, halfSize);

	// Initialize spaceship movement speed
	moveSpeed = 10.0f;

	// Initialize values to use when creating a missile
	missileHalfSize[0] = missileHalfSize[1] = 8.0f / 16.0f;
	missileVelocity[0] = 0.0f;
	missileVelocity[1] = -40.0f;

	// Start thread that manages firing cooldown
	cooldownThread = std::thread{ &Spaceship::cooldownCheck, this };

	// Load fire sound from file
	fireSound = Engine::getLevel()->loadSoundFile("../sounds/laser_fire.wav");
}

void Spaceship::update(float deltaTime)
{
	// Movement input
	if (Input::getInstance()->getKey("Right") && xpos < 566)
	{
		movementKeys[2] = true;
	}
	else
	{
		movementKeys[2] = false;
	}
	if (Input::getInstance()->getKey("Left") && xpos > 10)
	{
		movementKeys[0] = true;
	}
	else
	{
		movementKeys[0] = false;
	}

	if (movementKeys[2])
	{
		//moveRight(moveSpeed * deltaTime);
		moveRight(moveSpeed);
	}
	if (movementKeys[0])
	{
		//moveRight(-moveSpeed * deltaTime);
		moveRight(-moveSpeed);
	}
	if ((movementKeys[0] && movementKeys[2]) || (!movementKeys[0] && !movementKeys[2]))
	{
		// Reset velocity in x
		velocity[0] = 0.0f;
		rigidBody->setVelocity(velocity);
	}

	if (Input::getInstance()->getKey("Up") && ypos > 10)
	{
		movementKeys[1] = true;
	}
	else
	{
		movementKeys[1] = false;
	}
	if (Input::getInstance()->getKey("Down") && ypos < 406)
	{
		movementKeys[3] = true;
	}
	else
	{
		movementKeys[3] = false;
	}

	if (movementKeys[1])
	{
		//moveUp(moveSpeed * deltaTime);
		moveUp(moveSpeed);
	}
	if (movementKeys[3])
	{
		//moveUp(-moveSpeed * deltaTime);
		moveUp(-moveSpeed);
	}
	if ((movementKeys[1] && movementKeys[3]) || (!movementKeys[1] && !movementKeys[3]))
	{
		// Reset velocity in y
		velocity[1] = 0.0f;
		rigidBody->setVelocity(velocity);
	}

	// Game controller movement
	if (Input::getInstance()->getController(0))
	{
		float leftAxisX = Input::getInstance()->getController(0)->getLeftXAxis();
		float leftAxisY = Input::getInstance()->getController(0)->getLeftYAxis();

		if ((leftAxisX > 0.3f && xpos < 566) || (leftAxisX < -0.3f && xpos > 10))
		{
			//moveRight(moveSpeed * deltaTime * leftAxisX);
			moveRight(moveSpeed * leftAxisX);
		}
		if ((leftAxisY > 0.3f && ypos < 406) || (leftAxisY < -0.3f && ypos > 10 ))
		{
			//moveUp(moveSpeed * deltaTime * -leftAxisY);
			moveUp(moveSpeed * -leftAxisY);
		}

		if (Input::getInstance()->getController(0)->getButton("A"))
		{
			fire();
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


	// Update companions
	if (companionToAttach)
	{
		float offset[2]{ 0.0f, 0.0f };
		if (companionToAttach == attachedCompanions[0])
		{
			offset[0] = 3.5f;
			offset[1] = -0.5f;
		}
		if (companionToAttach == attachedCompanions[1])
		{
			offset[0] = -3.5f;
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
		Engine::getLevel()->playSound(fireSound, 0.5f);
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
	//std::cout << "Spaceship HP: " << health << std::endl;
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
	//std::cout << "Spaceship HP: " << health << std::endl;
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

