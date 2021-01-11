#pragma once

#include "Actor.h"
#include "Projectile.h"
#include "Tilemap.h"
#include "Animation.h"

class Missile :
	public Actor,
	public Projectile
{
public:
	Missile(float position[2], float halfSize[2], float density, float linearVelocity[2], uint16_t categoryBits, uint16_t maskBits);

	void update(float deltaTime) override;
	void onContact() override;

	~Missile();

private:
	Texture* explosionTex = nullptr;
	Tilemap* explosionTilemap = nullptr;
	Animation* explosionAnim = nullptr;
};

