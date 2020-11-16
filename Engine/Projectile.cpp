#include "Projectile.h"

#include <box2d/box2d.h>

Projectile::Projectile(float position[2], float halfSize[2], float linearVelocity[2])
{
	rigidBody.getBodyDef()->bullet = true;

	rigidBody.createBody(position, halfSize);
	rigidBody.setVelocity(linearVelocity);
}

Projectile::~Projectile()
{

}