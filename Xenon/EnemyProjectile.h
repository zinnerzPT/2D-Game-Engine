#pragma once

#include "Actor.h"
#include "Projectile.h"
#include "Tilemap.h"
#include "Animation.h"

class EnemyProjectile :
	public Actor,
	public Projectile
{
public:
	EnemyProjectile(float position[2], float halfSize[2], float density, float linearVelocity[2], uint16_t categoryBits, uint16_t maskBits, float damage);

	void update(float deltaTime) override;
	void onContact(ContactSensor* otherSensor = nullptr) override;

	~EnemyProjectile();

private:
	float projectileDamage = 0.0f;

	Texture* explosionTex = nullptr;
	Tilemap* explosionTilemap = nullptr;
	Animation* explosionAnim = nullptr;

	Animation* animationMedium = nullptr;
	Animation* animationHeavy = nullptr;
};

