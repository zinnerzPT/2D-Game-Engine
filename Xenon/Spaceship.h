#pragma once

#include "Pawn.h"

#include <thread>

class Spaceship : public Pawn
{
public:
	Spaceship(float x, float y);
	void update(float deltaTime);
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

	bool isAlive = true;

	float missileHalfSize[2];
	float missileVelocity[2];

	// Time it takes to fire again (in milliseconds)
	int cooldown = 200;

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

};

