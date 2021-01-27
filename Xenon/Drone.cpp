#include "Drone.h"
#define _USE_MATH_DEFINES
#include <math.h>

Drone::Drone(float x, float y, float offset) :Enemy(x, y)
{
	Texture* texture = new Texture("../graphics/drone.bmp");
	textures.push_back(texture);
	Tilemap* tilemap = new Tilemap(texture, 2, 8);
	tilemaps.push_back(tilemap);
	Animation* animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, true);
	animations.push_back(animation);
	animations[0]->play();

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
	Enemy::update(deltaTime);
	if (frameTime < moveDelay)
	{
		frameTime += deltaTime;
	}
	else
	{
		velocity[0] = 5 * sin(ypos * M_PI / 90);
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
