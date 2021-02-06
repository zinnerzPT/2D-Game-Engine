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
};

