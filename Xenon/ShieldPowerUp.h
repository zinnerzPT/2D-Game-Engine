#pragma once
#include "PowerUp.h"
class ShieldPowerUp :
    public PowerUp
{
public:
	ShieldPowerUp(int x, int y);
	void update(float deltaTime) override;
	void onContact(ContactSensor* otherSensor = nullptr) override;
	void applyPower(Spaceship* spaceship = nullptr) override;
	~ShieldPowerUp();
private:
	float velocity[2]{ 0.0f, 2.0f };
};

