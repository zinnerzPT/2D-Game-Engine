#include "Missile.h"
#include "RigidBody.h"
#include <iostream>

Missile::Missile(float position[2], float halfSize[2], float density, float linearVelocity[2]) : Projectile(position, halfSize, density, linearVelocity)
{
	Texture* texture = new Texture("../graphics/missile.bmp");
	textures.push_back(texture);

	tilemap = new Tilemap(texture, 3, 2);
	animation = new Animation(tilemap, { 0,1 }, true);
}

void Missile::update(float deltaTime)
{
	float* position;
	position = rigidBody->getPosition();

	textures[0]->setDstRect(position[0], position[1], tilemap->getTileWidth(), tilemap->getTileHeight());
}

void Missile::onContact()
{
	std::cout << "Collided" << std::endl;
}

Missile::~Missile()
{
	delete textures[0];
	delete tilemap;
	delete animation;
}
