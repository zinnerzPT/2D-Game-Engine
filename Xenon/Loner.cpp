#include "Loner.h"

Loner::Loner(float x, float y)
{
	Texture* texture = new Texture("../graphics/LonerA.bmp");
	textures.push_back(texture);
	tilemap = new Tilemap(texture, 4, 4);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, true);
	animation->play();

	rigidBody->makeDynamic(1.0f);
	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	rigidBody->createBody(position, halfSize);
	// Initialize velocity
	velocity[0] = 5.0f;
	rigidBody->setVelocity(velocity);

	// Initialize attack damage
	attackDamage = 20.0f;

	// Initialize values to use when creating a projectile
	projectileHalfSize[0] = projectileHalfSize[1] = 8.0f / 16.0f;
	projectileVelocity[0] = 0.0f;
	projectileVelocity[1] = 10.0f;
}

void Loner::update(float deltaTime)
{
	float* position;
	position = rigidBody->getPosition();
	position[0] = position[0] * 16.0f - tilemap->getTileWidth() / 2;
	xpos = position[0];
	position[1] = position[1] * 16.0f - tilemap->getTileHeight() / 2;
	ypos = position[1];
	textures[0]->setDstRect(position[0], position[1], tilemap->getTileWidth(), tilemap->getTileHeight());

	// For testing
	if (position[0] > 580 && !movementReversed)
	{
		movementReversed = true;
		velocity[0] *= -1;
		rigidBody->setVelocity(velocity);
	}
	if (position[0] < 0 && movementReversed)
	{
		movementReversed = false;
		velocity[0] *= -1;
		rigidBody->setVelocity(velocity);
	}

	chargingAttack += deltaTime;
	if (chargingAttack >= attackDelay) {
		chargingAttack = 0.0f;
		attack();
	}
}

void Loner::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	Enemy::onContact(otherSensor);
}

Loner::~Loner()
{

}

void Loner::attack()
{
	//Fire missiles
	float missilePosition[2]{ (xpos + 32) / 16.0f, (ypos + 64) / 16.0f };
	new EnemyProjectile(missilePosition, projectileHalfSize, 1.0f, projectileVelocity, CATEGORY_4, CATEGORY_1, attackDamage);
}
