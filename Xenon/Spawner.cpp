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
			randomNumber = rand() % 2;
			switch (randomNumber)
			{
			case 0:
				randomPosX = (rand() % 320) + 160;
				new Rusher(randomPosX, -40, VelocityDirection::positive);
				break;
			case 1:
				randomPosX = (rand() % 320) + 160;
				new Rusher(randomPosX, 520, VelocityDirection::negative);
				break;
			}
			return true;
		}
		break;
	case 1:
		if (lonerCooldownLeft <= 0)
		{
			lonerCooldownLeft = lonerCooldown;
			randomNumber = rand() % 2;
			randomPosY = (rand() % 200) + 80;
			switch (randomNumber)
			{
			case 0:
				new Loner(-70, randomPosY, VelocityDirection::positive);
				break;
			case 1:
				new Loner(710, randomPosY, VelocityDirection::negative);
				break;
			}
			return true;
		}
		break;
	case 2:
		if (droneCooldownLeft <= 0)
		{
			droneCooldownLeft = droneCooldown;
			randomNumber = rand() % 240 + 200;
			// delay before the drone starts moving
			float delay = 0;
			for (int i = 0; i < dronePack; ++i)
			{
				new Drone(randomNumber, -40, delay);
				delay += 0.6f;
			}
			return true;
		}
		break;
	case 3:
		break;
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
	randomPosX = (rand() % 440) + 100;
	switch (randomNumber)
	{
	case 0:
		if (shieldCooldownLeft <= 0)
		{
			shieldCooldownLeft = shieldCooldown;
			new ShieldPowerUp(randomPosX, -50);
			return true;
		}
		break;
	case 1:
		if (weaponCooldownLeft <= 0)
		{
			weaponCooldownLeft = weaponCooldown;
			new WeaponPowerUp(randomPosX, -50);
			return true;
		}
		break;
	case 2:
		if (companionCooldownLeft <= 0)
		{
			companionCooldownLeft = companionCooldown;
			new CompanionPowerUp(randomPosX, -50);
			return true;
		}
		break;
	}
	return false;
}
