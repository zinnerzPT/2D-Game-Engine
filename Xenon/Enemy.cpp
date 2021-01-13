#include "Enemy.h"
#include "Spaceship.h"
#include "CompanionPowerUp.h"
#include "GameManager.h"

Enemy::Enemy()
{
	// Enemy uses category 2 and collides with categories 1(player), 3(missile) and 6(companion)
	rigidBody->setCollisionFilter(CATEGORY_2, CATEGORY_1 | CATEGORY_3 | CATEGORY_6);
}

void Enemy::update(float deltaTime)
{
	float* position;
	position = rigidBody->getPosition();
	position[0] = position[0] * 16.0f - tilemap->getTileWidth() / 2;
	xpos = position[0];
	position[1] = position[1] * 16.0f - tilemap->getTileHeight() / 2;
	ypos = position[1];
	textures[0]->setDstRect(position[0], position[1], tilemap->getTileWidth(), tilemap->getTileHeight());
	if (position[1] > 500)
	{
		Actor::destroy();
	}
}

void Enemy::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	Spaceship* spaceship = nullptr;
	spaceship = dynamic_cast <Spaceship*> (otherSensor);
	if (spaceship)
	{
		spaceship->takeDamage(attackDamage);
	}

	CompanionPowerUp* companion = nullptr;
	companion = dynamic_cast <CompanionPowerUp*> (otherSensor);
	if (companion)
	{
		companion->takeDamage(attackDamage);
	}
}

void Enemy::takeDamage(float damage)
{
	if (health - damage > 0)
	{
		health -= damage;
	}
	else
	{
		health = 0;
		Actor::destroy();
		GameManager::getInstance()->addScore(points);
	}
}

Enemy::~Enemy()
{

}
