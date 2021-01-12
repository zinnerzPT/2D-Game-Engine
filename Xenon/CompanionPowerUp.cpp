#include "CompanionPowerUp.h"
#include "Spaceship.h"

// DEBUG PURPOSES ONLY
#include <iostream>

CompanionPowerUp::CompanionPowerUp(int x, int y)
{
	Texture* texture = new Texture("../graphics/clone.bmp");
	textures.push_back(texture);
	tilemap = new Tilemap(texture, 5, 4);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, true);
	animation->play();

	// This power up uses category 6 and collides with categories 1(player), 2(enemy), 4(enemy missile) and 5(power up)
	rigidBody->setCollisionFilter(CATEGORY_6, CATEGORY_1 | CATEGORY_2 | CATEGORY_4 | CATEGORY_5);
	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	rigidBody->createBody(position, halfSize);
	rigidBody->setVelocity(velocity);
}

void CompanionPowerUp::update(float deltaTime)
{
	PowerUp::update(deltaTime);
}

void CompanionPowerUp::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	PowerUp* powerUp = nullptr;
	powerUp = dynamic_cast <PowerUp*> (otherSensor);
	if (powerUp)
	{
		powerUp->applyPower(this);
	}
}

void CompanionPowerUp::applyPower(ContactSensor* sensor /*= nullptr*/)
{
	Spaceship* spaceship = nullptr;
	spaceship = dynamic_cast <Spaceship*> (sensor);
	if (spaceship)
	{
		spaceshipRef = spaceship;
		spaceship->attachCompanion(this);
	}
}


void CompanionPowerUp::addHealth(float additionalHealth)
{
	if (health + additionalHealth <= maxHealth)
	{
		health += additionalHealth;
	}
	else
	{
		health = maxHealth;
	}
	std::cout << "Companion HP: " << health << std::endl;
}


void CompanionPowerUp::takeDamage(float damage)
{
	if (health - damage > 0)
	{
		health -= damage;
	}
	else
	{
		health = 0;
		spaceshipRef->removeCompanion(this);
		Actor::destroy();
	}
	std::cout << "Companion HP: " << health << std::endl;
}

void CompanionPowerUp::upgradeMissile()
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

float* CompanionPowerUp::getPosition()
{
	return rigidBody->getPosition();
}

MissileType CompanionPowerUp::getMissileType()
{
	return missileType;
}

void CompanionPowerUp::setPosition(float pos[2])
{
	rigidBody->setPosition(pos);
}

void CompanionPowerUp::setVelocity(float vel[2])
{
	rigidBody->setVelocity(vel);
}

CompanionPowerUp::~CompanionPowerUp()
{

}
