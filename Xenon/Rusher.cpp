#include "Rusher.h"

Rusher::Rusher(float x, float y)
{
	texture = new Texture("../graphics/rusher.bmp");
	tilemap = new Tilemap(texture, 6, 4);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 }, true);

	rigidBody = new RigidBody();
	rigidBody->makeDynamic(1.0f);
	float position[2]{ x,y };
	float halfSize[2]{ tilemap->getTileWidth() / 8.0f, tilemap->getTileHeight() / 8.0f };
	rigidBody->createBody(position, halfSize);
	float velocity[2]{ 0.0f, -60.0f };
	rigidBody->setVelocity(velocity);
}

void Rusher::update(float deltaTime)
{
	float* position;
	position = rigidBody->getPosition();

	texture->setDstRect(position[0], position[1], tilemap->getTileWidth(), tilemap->getTileHeight());
}

Rusher::~Rusher()
{
	delete rigidBody;
}
