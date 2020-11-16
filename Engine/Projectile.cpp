#include "Projectile.h"

#include <box2d/box2d.h>

Projectile::Projectile(float position[2], float halfSize[2], float linearVelocity[2])
{
	rigidBody.getBodyDef()->userData.pointer = reinterpret_cast<uintptr_t>(this);
	rigidBody.getBodyDef()->bullet = true;
	rigidBody.getFixtureDef()->isSensor = true;

	rigidBody.createBody(position, halfSize);
	rigidBody.getBody()->SetLinearVelocity(b2Vec2(linearVelocity[0], linearVelocity[1]));
}

Projectile::~Projectile()
{

}