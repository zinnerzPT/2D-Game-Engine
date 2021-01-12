#include "Enemy.h"
#include "Spaceship.h"

Enemy::Enemy()
{
	// Enemy uses category 2 and collides with categories 1(player) and 3(missile)
	rigidBody->setCollisionFilter(CATEGORY_2, CATEGORY_1 | CATEGORY_3);
}

void Enemy::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	Spaceship* spaceship = nullptr;
	spaceship = dynamic_cast <Spaceship*> (otherSensor);
	if (spaceship)
	{
		spaceship->takeDamage(attackDamage);
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
