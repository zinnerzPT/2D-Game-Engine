#include "Loner.h"
#include "Engine.h"

Loner::Loner(float x, float y) {
	Texture* texture = new Texture("../graphics/LonerA.bmp");
	textures.push_back(texture);
	tilemap = new Tilemap(texture, 4, 4);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, true);
	animation->play();

	rigidBody = new RigidBody();
	rigidBody->makeDynamic(1.0f);
	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	rigidBody->createBody(position, halfSize);

	rigidBody->setVelocity(velocity);
}




void Loner::update(float deltaTime)
{
	float* position;
	position = rigidBody->getPosition();
	position[0] = position[0] * 16.0f - tilemap->getTileWidth() / 2;
	if (position[0] > 580 && !movementReversed)
	{
		movementReversed = true;
		velocity[0] *= -1;
		rigidBody->setVelocity(velocity);
	}
	if (position[0] < 10 && movementReversed)
	{
		movementReversed = false;
		velocity[0] *= -1;
		rigidBody->setVelocity(velocity);
	}
	position[1] = position[1] * 16.0f - tilemap->getTileHeight() / 2;
	textures[0]->setDstRect(position[0], position[1], tilemap->getTileWidth(), tilemap->getTileHeight());
}

Loner::~Loner()
{
	delete rigidBody;
}
