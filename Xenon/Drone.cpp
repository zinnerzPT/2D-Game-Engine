#include "Drone.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

Drone::Drone(float x, float y, float offset)
{
	Texture* texture = new Texture("../graphics/drone.bmp");
	textures.push_back(texture);
	tilemap = new Tilemap(texture, 2, 8);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, true);
	animation->play();

	rigidBody->makeDynamic(1.0f);
	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	rigidBody->createBody(position, halfSize);
	
	this->moveDelay = offset;
	
	// Initialize velocity on  the y axis
	velocity[1] = 5.0f;
	// Initialize attack damage
	attackDamage = 15.0f;
	// Initialize health
	health = 50.0f;
}

void Drone::update(float deltaTime)
{
	float* position;
	position = rigidBody->getPosition();
	position[0] = position[0] * 16.0f - tilemap->getTileWidth() / 2;
	position[1] = position[1] * 16.0f - tilemap->getTileHeight() / 2;
	textures[0]->setDstRect(position[0], position[1], tilemap->getTileWidth(), tilemap->getTileHeight());
	if (position[1] > 500)
	{
		Actor::destroy();
	}
	if (frameTime < moveDelay)
	{
		frameTime += deltaTime;
	}
	else
	{
		velocity[0] = 5 * sin(position[1] * M_PI / 90);
		rigidBody->setVelocity(velocity);
	}
}

void Drone::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	Enemy::onContact(otherSensor);
}

Drone::~Drone()
{

}
