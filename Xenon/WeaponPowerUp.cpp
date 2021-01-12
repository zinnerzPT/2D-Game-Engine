#include "WeaponPowerUp.h"
#include "Animation.h"

WeaponPowerUp::WeaponPowerUp(int x, int y)
{
	Texture* texture = new Texture("../graphics/PUWeapon.bmp");
	textures.push_back(texture);
	tilemap = new Tilemap(texture, 2, 4);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7 }, true);
	animation->play();

	rigidBody->makeDynamic(1.0f);
	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	rigidBody->setCollisionFilter(CATEGORY_5, CATEGORY_1);
	rigidBody->createBody(position, halfSize);

	rigidBody->setVelocity(velocity);
}

void WeaponPowerUp::update(float deltaTime)
{
	float* position;
	position = rigidBody->getPosition();
	position[0] = position[0] * 16.0f - tilemap->getTileWidth() / 2;
	position[1] = position[1] * 16.0f - tilemap->getTileHeight() / 2;
	textures[0]->setDstRect(position[0], position[1], tilemap->getTileWidth(), tilemap->getTileHeight());
	if (position[1] > 500)
	{
		Actor::destroy();
	}
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
