#include "Rusher.h"

Rusher::Rusher(float x, float y)
{
	Texture* texture = new Texture("../graphics/rusher.bmp");
	textures.push_back(texture);

	tilemap = new Tilemap(texture, 6, 4);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 }, true);
	animation->play();

	rigidBody = new RigidBody();
	rigidBody->makeDynamic(1.0f);
	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	rigidBody->setCollisionFilter(CATEGORY_2, CATEGORY_3);
	rigidBody->createBody(position, halfSize);

	float velocity[2]{ 0.0f, -3.75f };
	rigidBody->setVelocity(velocity);
}

void Rusher::update(float deltaTime)
{
	float* position;
	position = rigidBody->getPosition();
	position[0] = position[0] * 16.0f - tilemap->getTileWidth() / 2;
	position[1] = position[1] * 16.0f - tilemap->getTileHeight() / 2;
	textures[0]->setDstRect(position[0], position[1], tilemap->getTileWidth(), tilemap->getTileHeight());
}

Rusher::~Rusher()
{
	delete rigidBody;
}
