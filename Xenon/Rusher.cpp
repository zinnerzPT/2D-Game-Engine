#include "Rusher.h"

Rusher::Rusher(float x, float y, VelocityDirection velocityDirection /*= VelocityDirection::positive*/) :Enemy(x, y)
{
	Texture* texture = new Texture("../graphics/rusher.bmp");
	textures.push_back(texture);
	Tilemap* tilemap = new Tilemap(texture, 6, 4);
	tilemaps.push_back(tilemap);
	Animation* animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 }, true);
	animations.push_back(animation);
	animations[0]->play();

	rigidBody->makeDynamic(1.0f);
	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	rigidBody->createBody(position, halfSize);
	// Initialize velocity
	if (velocityDirection == VelocityDirection::negative)
	{
		rusherVelocity *= -1;
		flipVertical = true;
	}
	velocity[1] = rusherVelocity;
	rigidBody->setVelocity(velocity);

	// Initialize attack damage
	attackDamage = 20.0f;
}

void Rusher::update(float deltaTime)
{
	Enemy::update(deltaTime);
}

void Rusher::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	Enemy::onContact(otherSensor);
}

Rusher::~Rusher()
{

}
