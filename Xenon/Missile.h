#pragma once

#include "Actor.h"
#include "Projectile.h"
#include "Tilemap.h"
#include "Animation.h"

enum class MissileType
{
	light,
	medium,
	heavy
};

class Missile :
	public Actor,
	public Projectile
{
public:
	Missile(float position[2], float halfSize[2], float density, float linearVelocity[2], uint16_t categoryBits, uint16_t maskBits, MissileType type);

	void update(float deltaTime) override;
	void onContact(ContactSensor* otherSensor = nullptr) override;

	~Missile();

private:
	float missileDamage = 0.0f;
	float lightDamage = 25.0f;
	float mediumDamage = lightDamage * 2;
	float heavyDamage = mediumDamage * 2;

	Texture* explosionTex = nullptr;
	Tilemap* explosionTilemap = nullptr;
	Animation* explosionAnim = nullptr;
};

