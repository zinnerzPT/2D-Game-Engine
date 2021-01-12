#include "ShieldPowerUp.h"
#include "Animation.h"

ShieldPowerUp::ShieldPowerUp(int x, int y)
{
	Texture* texture = new Texture("../graphics/PUShield.bmp");
	textures.push_back(texture);
	tilemap = new Tilemap(texture, 2, 4);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7 }, true);
	animation->play();

	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	rigidBody->createBody(position, halfSize);
	rigidBody->setVelocity(velocity);
}

void ShieldPowerUp::update(float deltaTime)
{
	PowerUp::update(deltaTime);
}

void ShieldPowerUp::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	Spaceship* spaceship = nullptr;
	spaceship = dynamic_cast <Spaceship*> (otherSensor);
	if (spaceship)
	{
		Actor::destroy();
	}
}

void ShieldPowerUp::applyPower(Spaceship* spaceship)
{
	if (spaceship)
	{
		spaceship->addHealth(50.0f);
	}
}

ShieldPowerUp::~ShieldPowerUp()
{

}
