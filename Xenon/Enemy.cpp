#include "Enemy.h"

void Enemy::takeDamage(float damage)
{
	health -= damage;
	if (health <= 0)
	{
		Actor::destroy();
	}
}

Enemy::~Enemy()
{

}
