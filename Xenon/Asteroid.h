#pragma once
#include "Enemy.h"

enum class AsteroidType
{
	stone,
	metal
};

enum class AsteroidSize
{
	small,
	medium,
	large
};

class Asteroid :
	public Enemy
{
public:
	Asteroid(float x, float y, AsteroidType type = AsteroidType::stone, AsteroidSize size = AsteroidSize::small);
	void update(float deltaTime);
	void onContact(ContactSensor* otherSensor = nullptr) override;
	void takeDamage(float damage) override;
	void spawnSmallerAsteroid(float location[2]);
	~Asteroid();

private:
	bool toDestroy = false;
	// Number of asteroids to split into
	int asteroidsToSplit = 3;

	//Damage dealt by the small asteroid
	float smallDamage = 15.0f; 
	//Damage dealt by the medium asteroid
	float mediumDamage = smallDamage * 2;
	//Damage dealt by the large asteroid
	float largeDamage = mediumDamage * 2;

	//Health of the small asteroid
	float smallHealth = 25.0f;
	//Health of the medium asteroid
	float mediumHealth = smallHealth * 2;
	//Health of the large asteroid
	float largeHealth = mediumHealth * 2;

	AsteroidType asteroidType = AsteroidType::stone;
	AsteroidSize asteroidSize = AsteroidSize::small;
};

