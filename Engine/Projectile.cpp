#include "Projectile.h"

#include <box2d/box2d.h>

#include "Engine.h"

Projectile::Projectile(float position[2], float halfSize[2], float density, float linearVelocity[2], uint16_t categoryBits, uint16_t maskBits)
{
	rigidBody->getBodyDef()->bullet = true;
	rigidBody->makeDynamic(density);
	rigidBody->setCollisionFilter(categoryBits, maskBits);
	rigidBody->createBody(position, halfSize);

	rigidBody->setVelocity(linearVelocity);
}
