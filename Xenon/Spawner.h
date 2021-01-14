#pragma once
#include "Actor.h"

class Spawner : public Actor
{
public:
	Spawner();
	void update(float deltaTime) override;

private:
	bool spawnEnemies();
	bool spawnPowerUp();

	int randomNumber = 0;
	int randomPosX = 0;
	int randomPosY = 0;
	// amount of drones to spawn in a pack
	int dronePack = 5;

	// Seconds to wait before spawning an enemy again
	float enemyCooldown = 2.0f;
	float enemyCooldownLeft = enemyCooldown;
	// Seconds to wait before spawning a loner again
	float lonerCooldown = 2.5f;
	float lonerCooldownLeft = 0.0f;
	// Seconds to wait before spawning a rusher again
	float rusherCooldown = 2.0f;
	float rusherCooldownLeft = 0.0f;
	// Seconds to wait before spawning drones again
	float droneCooldown = 15.0f;
	float droneCooldownLeft = 0.0f;
	// Seconds to wait before spawning asteroids again
	float asteroidCooldown = 15.0f;
	float asteroidCooldownLeft = 0.0f;

	// Seconds to wait before spawning a power up again
	float powerUpCooldown = 10.0f;
	float powerUpCooldownLeft = powerUpCooldown;
	// Seconds to wait before spawning a shield power up again
	float shieldCooldown = 10.0f;
	float shieldCooldownLeft = 0.0f;
	// Seconds to wait before spawning a weapon power up again
	float weaponCooldown = 15.0f;
	float weaponCooldownLeft = 0.0f;
	// Seconds to wait before spawning a companion power up again
	float companionCooldown = 20.0f;
	float companionCooldownLeft = 0.0f;
};

