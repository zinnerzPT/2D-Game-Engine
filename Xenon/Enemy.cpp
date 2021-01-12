#include "Enemy.h"
#include "Engine.h"
#include "Level.h"

void Enemy::takeDamage(float damage)
{
	health -= damage;
	if (health <= 0)
	{
		Engine::getLevel()->addActorToRemove(this);
	}
}

Enemy::~Enemy()
{

}
