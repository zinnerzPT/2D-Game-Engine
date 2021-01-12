#pragma once
#include "PowerUp.h"
class WeaponPowerUp :
    public PowerUp
{
public:
	WeaponPowerUp(int x, int y);
	void update(float deltaTime) override;
	void onContact(ContactSensor* otherSensor = nullptr) override;
	void applyPower(ContactSensor* sensor = nullptr) override;
	~WeaponPowerUp();
private:
	float velocity[2]{ 0.0f, 2.0f };
};

