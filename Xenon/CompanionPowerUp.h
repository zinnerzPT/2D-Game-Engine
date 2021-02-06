#pragma once
#include "PowerUp.h"
#include "Missile.h"

class CompanionPowerUp :
    public PowerUp
{
public:
	CompanionPowerUp(int x, int y);
	void update(float deltaTime) override;
	void onContact(ContactSensor* otherSensor = nullptr) override;
	void applyPower(ContactSensor* sensor = nullptr) override;

	void addHealth(float additionalHealth);
	void takeDamage(float damage);
	void upgradeMissile();

	float* getPosition();
	MissileType getMissileType();
	void setPosition(float pos[2]);
	void setVelocity(float vel[2]);
	~CompanionPowerUp();

private:
	float health = 60.0f;
	float maxHealth = 60.0f;
	MissileType missileType = MissileType::light;
	class Spaceship* spaceshipRef;
};

