#pragma once
#include "PowerUp.h"
class CompanionPowerUp :
    public PowerUp
{
public:
	CompanionPowerUp(int x, int y);
	void update(float deltaTime) override;
	void onContact(ContactSensor* otherSensor = nullptr) override;
	void applyPower(Spaceship* spaceship = nullptr) override;

	float* getPosition();
	void setPosition(float pos[2]);
	void setVelocity(float vel[2]);
	~CompanionPowerUp();
private:
	float velocity[2]{ 0.0f, 2.0f };
};

