#include "Loner.h"

Loner::Loner(float x, float y, VelocityDirection velocityDirection /*= VelocityDirection::positive*/)
{
	Texture* texture = new Texture("../graphics/LonerA.bmp");
	textures.push_back(texture);
	flipHorizontal = true;
	Tilemap* tilemap = new Tilemap(texture, 4, 4);
	tilemaps.push_back(tilemap);
	Animation* animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, true);
	animations.push_back(animation);
	animations[0]->play();

	rigidBody->makeDynamic(1.0f);
	float position[2]{ x / 16.0f, y / 16.0f };
	float halfSize[2]{ (tilemap->getTileWidth() / 16.0f) / 2.0f, (tilemap->getTileHeight() / 16.0f) / 2.0f };
	rigidBody->createBody(position, halfSize);
	// Initialize velocity
	if (velocityDirection == VelocityDirection::negative)
	{
		lonerVelocity *= -1;
		flipHorizontal = false;
	}
	velocity[0] = lonerVelocity;
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
	Enemy::update(deltaTime);
	chargingAttack += deltaTime;
	if (chargingAttack >= attackDelay) {
		chargingAttack = 0.0f;
		attack();
	}
}

void Loner::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	Enemy::onContact(otherSensor);
	if (xpos > 640)
	{
		Actor::destroy();
	}
}

Loner::~Loner()
{

}

void Loner::attack()
{
	//Fire missiles
	float missilePosition[2]{ (xpos + 32) / 16.0f, (ypos + 64) / 16.0f };
	// EnemyProjectile uses category 4 and collides with categories 1(player) and 6(companion)
	new EnemyProjectile(missilePosition, projectileHalfSize, 1.0f, projectileVelocity, CATEGORY_4, CATEGORY_1 | CATEGORY_6, attackDamage);
}
