#pragma once

#include "Pawn.h"
#include "Missile.h"
#include "Sound.h"

#include <thread>

class Spaceship :
	public Pawn
{
public:
	Spaceship(float x, float y);
	void update(float deltaTime);
	void onContact(ContactSensor* otherSensor = nullptr) override;

	void addHealth(float additionalHealth);
	float getHealth() { return health; }
	void takeDamage(float damage);
	void upgradeMissile();
	void attachCompanion(class CompanionPowerUp* companion);
	void removeCompanion(class CompanionPowerUp* companion);
	float* getPosition();
	~Spaceship();

private:
	void fire();
	void cooldownCheck();

	void stopTurningAnims();
	void animateMoveRight();
	void animateMoveLeft();
	void animateReturnRight();
	void animateReturnLeft();

	bool isMovingRight = false;
	bool isMovingLeft = false;

	bool canFire = true;
	bool needsCooldown = false;

	// 0 for left, 1 for up, 2 for right and 3 for down
	bool movementKeys[4] = { false, false, false, false };

	bool isAlive = true;

	float missileHalfSize[2];
	float missileVelocity[2];

	float health = 100.0f;
	float maxHealth = 100.0f;

	// Time it takes to fire again (in milliseconds)
	int cooldown = 300;

	std::vector<class CompanionPowerUp*> attachedCompanions{ nullptr, nullptr };
	class CompanionPowerUp* companionToAttach = nullptr;

	Animation* moveRightAnim;
	Animation* moveLeftAnim;

	Animation* returnRightAnim;
	Animation* returnLeftAnim;

	Texture* burnerTexRight = nullptr;
	Tilemap* burnerTilemapRight = nullptr;
	Animation* burnerAnimRight = nullptr;

	Texture* burnerTexLeft = nullptr;
	Tilemap* burnerTilemapLeft = nullptr;
	Animation* burnerAnimLeft = nullptr;

	std::thread cooldownThread;
	MissileType missileType = MissileType::light;

	Sound* fireSound = nullptr;
};

