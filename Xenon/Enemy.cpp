#include "Enemy.h"
#include "Spaceship.h"
#include "CompanionPowerUp.h"

Enemy::Enemy()
{
	// Enemy uses category 2 and collides with categories 1(player), 3(missile) and 6(companion)
	rigidBody->setCollisionFilter(CATEGORY_2, CATEGORY_1 | CATEGORY_3 | CATEGORY_6);
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
	}
}

Enemy::~Enemy()
{

}
