#include "Asteroid.h"

Asteroid::Asteroid(float x, float y, AsteroidType type /*= AsteroidType::stone*/, AsteroidSize size /*= AsteroidSize::small*/)
{
	Texture* texture = nullptr;

	asteroidSize = size;
	asteroidType = type;

	switch (asteroidSize)
	{
		// Small Asteroid
	case AsteroidSize::small:
		switch (asteroidType)
		{
		case AsteroidType::stone:
			texture = new Texture("../graphics/SAster32.bmp");
			break;
		case AsteroidType::metal:
			texture = new Texture("../graphics/MAster32.bmp");
			break;
		}
		textures.push_back(texture);
		tilemap = new Tilemap(texture, 2, 8);
		animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, true);
		// Initialize corresponding damage
		attackDamage = smallDamage;
		// Initialize corresponding health
		health = smallHealth;
		break;

		// Medium Asteroid
	case AsteroidSize::medium:
		switch (asteroidType)
		{
		case AsteroidType::stone:
			texture = new Texture("../graphics/SAster64.bmp");
			break;
		case AsteroidType::metal:
			texture = new Texture("../graphics/MAster64.bmp");
			break;
		}
		textures.push_back(texture);
		tilemap = new Tilemap(texture, 3, 8);
		animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 }, true);
		// Initialize corresponding damage
		attackDamage = mediumDamage;
		// Initialize corresponding health
		health = mediumHealth;
		break;

		// Large Asteroid
	case AsteroidSize::large:
		switch (asteroidType)
		{
		case AsteroidType::stone:
			texture = new Texture("../graphics/SAster96.bmp");
			break;
		case AsteroidType::metal:
			texture = new Texture("../graphics/MAster96.bmp");
			break;
		}
		textures.push_back(texture);
		tilemap = new Tilemap(texture, 5, 5);
		animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 }, true);
		// Initialize corresponding damage
		attackDamage = largeDamage;
		// Initialize corresponding health
		health = largeHealth;
		break;
	}
	animation->play();

	rigidBody->makeDynamic(1.0f);
	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	rigidBody->createBody(position, halfSize);
	// Initialize velocity
	velocity[1] = 4.0f;
	rigidBody->setVelocity(velocity);
}

void Asteroid::update(float deltaTime)
{
	Enemy::update(deltaTime);
	if (toDestroy)
	{
		toDestroy = false;
		float xOffset = -6;
		float yOffset = 2;
		for (int i = 0; i < asteroidsToSplit; ++i)
		{
			float location[2]{ rigidBody->getPosition()[0] + xOffset + (i + 1) * 3, rigidBody->getPosition()[1] + yOffset};
			spawnSmallerAsteroid(location);
		}
		Actor::destroy();
	}
}

void Asteroid::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	Enemy::onContact(otherSensor);
}

void Asteroid::takeDamage(float damage)
{
	switch (asteroidType)
	{
	case AsteroidType::stone:
		if (health - damage > 0)
		{
			health -= damage;
		}
		else
		{
			health = 0;
			toDestroy = true;
		}
		break;
	case AsteroidType::metal:
		break;
	}
}

void Asteroid::spawnSmallerAsteroid(float location[2])
{
	switch (asteroidSize)
	{
	case AsteroidSize::small:
		break;
	case AsteroidSize::medium:
		new Asteroid(location[0] * 16.0f, location[1] * 16.0f, AsteroidType::stone, AsteroidSize::small);
		break;
	case AsteroidSize::large:
		new Asteroid(location[0] * 16.0f, location[1] * 16.0f, AsteroidType::stone, AsteroidSize::medium);
		break;
	}
}

Asteroid::~Asteroid()
{

}
