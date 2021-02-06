#include "ShieldPowerUp.h"
#include "Animation.h"
#include "Spaceship.h"
#include "CompanionPowerUp.h"

ShieldPowerUp::ShieldPowerUp(int x, int y) : PowerUp(x, y)
{
	Texture* texture = new Texture("../graphics/PUShield.bmp");
	textures.push_back(texture);
	Tilemap* tilemap = new Tilemap(texture, 2, 4);
	tilemaps.push_back(tilemap);
	Animation* animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7 }, true);
	animations.push_back(animation);
	animations[0]->play();

	// This power up uses category 5 and collides with category 1(player) and 6(companion)
	rigidBody->setCollisionFilter(CATEGORY_5, CATEGORY_1 | CATEGORY_6);
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
	CompanionPowerUp* companion = nullptr;
	companion = dynamic_cast <CompanionPowerUp*> (otherSensor);
	if (spaceship || companion)
	{
		Actor::destroy();
	}
}

void ShieldPowerUp::applyPower(ContactSensor* sensor)
{
	Spaceship* spaceship = nullptr;
	spaceship = dynamic_cast <Spaceship*> (sensor);
	if (spaceship)
	{
		spaceship->addHealth(bonusHealth);
	}
	CompanionPowerUp* companion = nullptr;
	companion = dynamic_cast <CompanionPowerUp*> (sensor);
	if (companion)
	{
		companion->addHealth(bonusHealth);
	}
}

ShieldPowerUp::~ShieldPowerUp()
{

}
