#include "WeaponPowerUp.h"
#include "Animation.h"

WeaponPowerUp::WeaponPowerUp(int x, int y)
{
	Texture* texture = new Texture("../graphics/PUWeapon.bmp");
	textures.push_back(texture);
	tilemap = new Tilemap(texture, 2, 4);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7 }, true);
	animation->play();

	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	rigidBody->createBody(position, halfSize);
	rigidBody->setVelocity(velocity);
}

void WeaponPowerUp::update(float deltaTime)
{
	PowerUp::update(deltaTime);
}

void WeaponPowerUp::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	Spaceship* spaceship = nullptr;
	spaceship = dynamic_cast <Spaceship*> (otherSensor);
	if (spaceship)
	{
		Actor::destroy();
	}
}

void WeaponPowerUp::applyPower(Spaceship* spaceship /*= nullptr*/)
{
	if (spaceship)
	{
		spaceship->upgradeMissile();
	}
}

WeaponPowerUp::~WeaponPowerUp()
{

}
