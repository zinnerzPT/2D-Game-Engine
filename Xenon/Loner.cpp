#include "Loner.h"

Loner::Loner()
{
	texture = new Texture("../graphics/LonerA.bmp");
	tilemap = new Tilemap(texture, 4, 4);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, true);
	
	rigidBody = new RigidBody();
	rigidBody->makeDynamic(1.0f);
	float position[2]{ 0.0f,0.0f };
	float halfSize[2]{ tilemap->getTileWidth() / 8.0f, tilemap->getTileHeight() / 8.0f };
	rigidBody->createBody(position, halfSize);
	float velocity[2]{ 60.0f, 0.0f };
	rigidBody->setVelocity(velocity);
}

void Loner::update(float deltaTime)
{
	float* position;
	position = rigidBody->getPosition();
	
	texture->setDstRect(position[0], position[1], tilemap->getTileWidth(), tilemap->getTileHeight());
}

Loner::~Loner()
{
	delete rigidBody;
}
