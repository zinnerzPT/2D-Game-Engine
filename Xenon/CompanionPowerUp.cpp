#include "CompanionPowerUp.h"

CompanionPowerUp::CompanionPowerUp(int x, int y)
{
	Texture* texture = new Texture("../graphics/clone.bmp");
	textures.push_back(texture);
	tilemap = new Tilemap(texture, 5, 4);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, true);
	animation->play();

	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	rigidBody->createBody(position, halfSize);
	rigidBody->setVelocity(velocity);
}

void CompanionPowerUp::update(float deltaTime)
{
	PowerUp::update(deltaTime);
}

void CompanionPowerUp::onContact(ContactSensor* otherSensor /*= nullptr*/)
{

}

void CompanionPowerUp::applyPower(Spaceship* spaceship /*= nullptr*/)
{
	if (spaceship)
	{
		spaceship->attachCompanion(this);
	}
}

float* CompanionPowerUp::getPosition()
{
	return rigidBody->getPosition();
}

void CompanionPowerUp::setPosition(float pos[2])
{
	rigidBody->setPosition(pos);
}

void CompanionPowerUp::setVelocity(float vel[2])
{
	rigidBody->setVelocity(vel);
}

CompanionPowerUp::~CompanionPowerUp()
{

}
