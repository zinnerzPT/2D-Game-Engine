#include "EnemyProjectile.h"
#include "RigidBody.h"
#include "Spaceship.h"

EnemyProjectile::EnemyProjectile(float position[2], float halfSize[2], float density, float linearVelocity[2], uint16_t categoryBits, uint16_t maskBits, float damage)
	: Projectile(position, halfSize, density, linearVelocity, categoryBits, maskBits)
{
	// Projectile texture
	Texture* texture = new Texture("../graphics/EnWeap6.bmp");
	textures.push_back(texture);

	// Projectile animation
	Tilemap* tilemap = new Tilemap(texture, 1, 8);
	tilemaps.push_back(tilemap);
	Animation* animation = new Animation(tilemap, { 0,1,2,3,4,5,6,7 }, true);
	animations.push_back(animation);
	animations[0]->play();

	// Explosion texture and Animation
	explosionTex = new Texture("../graphics/explode16.bmp");
	explosionTilemap = new Tilemap(explosionTex, 2, 5);
	explosionAnim = new Animation(explosionTilemap, { 0,1,2,3,4,5,6,7,8,9 }, false);
	animations.push_back(explosionAnim);

	// Set damage
	projectileDamage = damage;
}

void EnemyProjectile::update(float deltaTime)
{
	float* position;
	position = rigidBody->getPosition();
	position[0] = position[0] * 16.0f - tilemaps[0]->getTileWidth() / 2;
	position[1] = position[1] * 16.0f - tilemaps[0]->getTileHeight() / 2;
	textures[0]->setDstRect(position[0], position[1], tilemaps[0]->getTileWidth(), tilemaps[0]->getTileHeight());
	explosionTex->setDstRect(position[0], position[1], tilemaps[0]->getTileWidth(), tilemaps[0]->getTileHeight());
	// destroy it if goes out of bounds
	if (position[1] < -10 || position[1] > 490)
	{
		Actor::destroy();
	}
}

void EnemyProjectile::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	float velocityZero[2]{ 0.0f, 0.0f };
	rigidBody->setVelocity(velocityZero);
	animations[0]->stop();
	textures[0] = explosionTex;
	explosionAnim->play();
	explosionAnim->destroyAfterEnd(this);
	rigidBody->setEnabled(false);

	Spaceship* ship = nullptr;
	ship = dynamic_cast <Spaceship*> (otherSensor);
	if (ship)
	{
		ship->takeDamage(projectileDamage);
	}
}

EnemyProjectile::~EnemyProjectile()
{

}
