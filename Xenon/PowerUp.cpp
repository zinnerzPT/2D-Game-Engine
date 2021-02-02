#include "PowerUp.h"

PowerUp::PowerUp()
{
	rigidBody->makeDynamic(1.0f);
}

void PowerUp::update(float deltaTime)
{
	float* position;
	position = rigidBody->getPosition();
	position[0] = position[0] * 16.0f - tilemaps[0]->getTileWidth() / 2;
	position[1] = position[1] * 16.0f - tilemaps[0]->getTileHeight() / 2;
	//textures[0]->setDstRect(position[0], position[1], tilemaps[0]->getTileWidth(), tilemaps[0]->getTileHeight());
	if (position[1] > 500)
	{
		Actor::destroy();
	}
}

PowerUp::~PowerUp()
{

}
