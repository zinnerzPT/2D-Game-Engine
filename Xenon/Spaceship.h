#pragma once

#include "Pawn.h"


class Spaceship : public Pawn
{
public:
	Spaceship(float x, float y);
	void update(float deltaTime);

private:
	void fire();
	void stopTurningAnims();

	bool isMovingRight = false;
	bool isMovingLeft = false;

	float missileHalfSize[2];
	float missileVelocity[2];

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

};

