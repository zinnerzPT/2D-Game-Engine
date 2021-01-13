#include "Spawner.h"
// Enemies
#include "Loner.h"
#include "Rusher.h"
#include "Drone.h"
#include "Asteroid.h"
// Power ups
#include "ShieldPowerUp.h"
#include "WeaponPowerUp.h"
#include "CompanionPowerUp.h"

#include <time.h>

//DEBUG PURPOSES ONLY
#include <iostream>

Spawner::Spawner()
{
	srand(time(NULL));
}

void Spawner::update(float deltaTime)
{
	enemyCooldownLeft -= deltaTime;
	lonerCooldownLeft -= deltaTime;
	rusherCooldownLeft -= deltaTime;
	droneCooldownLeft -= deltaTime;
	asteroidCooldownLeft -= deltaTime;

	if (enemyCooldownLeft <= 0)
	{
		if (spawnEnemies())
		{
			enemyCooldownLeft = enemyCooldown;
			//std::cout << "-------------- Enemies on cooldown --------------" << std::endl;
		}
	}

	powerUpCooldownLeft -= deltaTime;
	shieldCooldownLeft -= deltaTime;
	weaponCooldownLeft -= deltaTime;
	companionCooldownLeft -= deltaTime;

	if (powerUpCooldownLeft <= 0)
	{
		if (spawnPowerUp())
		{
			powerUpCooldownLeft = powerUpCooldown;
			//std::cout << "-------------- Power up on cooldown --------------" << std::endl;
		}
	}
}

bool Spawner::spawnEnemies()
{
	randomNumber = rand() % 4;
	//std::cout << "Random number (enemy): " << randomNumber << std::endl;
	switch (randomNumber)
	{
	case 0:
		if (rusherCooldownLeft <= 0)
		{
			rusherCooldownLeft = rusherCooldown;
			new Rusher(400, -40);
			return true;
		}
		break;
	case 1:
		if (lonerCooldownLeft <= 0)
		{
			lonerCooldownLeft = lonerCooldown;
			new Loner(-70, 180);
			return true;
		}
		break;
	case 2:
		if (droneCooldownLeft <= 0)
		{
			droneCooldownLeft = droneCooldown;
			new Drone(250, -40);
			new Drone(250, -40, .6f);
			new Drone(250, -40, 1.2f);
			new Drone(250, -40, 1.8f);
			new Drone(250, -40, 2.4f);
			return true;
		}
		break;
	case 3:
		if (asteroidCooldownLeft <= 0)
		{
			asteroidCooldownLeft = asteroidCooldown;
			new Asteroid(80, -150, AsteroidType::stone, AsteroidSize::medium);
			new Asteroid(560, -150, AsteroidType::stone, AsteroidSize::medium);
			new Asteroid(160, -100, AsteroidType::metal, AsteroidSize::medium);
			new Asteroid(480, -100, AsteroidType::metal, AsteroidSize::medium);
			new Asteroid(320, -200, AsteroidType::stone, AsteroidSize::large);
			return true;
		}
		break;
	}
	return false;
}

bool Spawner::spawnPowerUp()
{
	randomNumber = rand() % 3;
	//std::cout << "Random number (power up): " << randomNumber << std::endl;
	switch (randomNumber)
	{
	case 0:
		if (shieldCooldownLeft <= 0)
		{
			shieldCooldownLeft = shieldCooldown;
			new ShieldPowerUp(100, -50);
			return true;
		}
		break;
	case 1:
		if (weaponCooldownLeft <= 0)
		{
			weaponCooldownLeft = weaponCooldown;
			new WeaponPowerUp(100, -50);
			return true;
		}
		break;
	case 2:
		if (companionCooldownLeft <= 0)
		{
			companionCooldownLeft = companionCooldown;
			new CompanionPowerUp(540, -50);
			return true;
		}
		break;
	}
	return false;
}
