#include "Missile.h"
#include "RigidBody.h"
#include "Enemy.h"

Missile::Missile(float position[2], float halfSize[2], float density, float linearVelocity[2], uint16_t categoryBits, uint16_t maskBits, MissileType type)
	: Actor(position[0] * 16, position[1] * 16),
	Projectile(position, halfSize, density, linearVelocity, categoryBits, maskBits)
{
	Texture* texture = new Texture("../graphics/missile.bmp");
	textures.push_back(texture);
	Animation* animation = nullptr;

	Tilemap* tilemap = new Tilemap(texture, 3, 2);
	tilemaps.push_back(tilemap);
	switch (type)
	{
	case MissileType::light:
		animation = new Animation(tilemap, { 0,1 }, true);
		animations.push_back(animation);
		missileDamage = lightDamage;
		break;
	case MissileType::medium:
		tilemap->ChangeFrame(2);
		animation = new Animation(tilemap, { 2,3 }, true);
		animations.push_back(animation);
		missileDamage = mediumDamage;
		break;
	case MissileType::heavy:
		tilemap->ChangeFrame(4);
		animation = new Animation(tilemap, { 4,5 }, true);
		animations.push_back(animation);
		missileDamage = heavyDamage;
		break;
	}
	animations[0]->play();

	explosionTex = new Texture("../graphics/explode16.bmp");
	explosionTilemap = new Tilemap(explosionTex, 2, 5);
	tilemaps.push_back(explosionTilemap);
	explosionAnim = new Animation(explosionTilemap, { 0,1,2,3,4,5,6,7,8,9 }, false);
	animations.push_back(explosionAnim);
}

void Missile::update(float deltaTime)
{
	float* position;
	position = rigidBody->getPosition();
	position[0] = position[0] * 16.0f - tilemaps[0]->getTileWidth() / 2;
	xpos = position[0];
	position[1] = position[1] * 16.0f - tilemaps[0]->getTileHeight() / 2;
	ypos = position[1];
	//textures[0]->setDstRect(position[0], position[1], tilemaps[0]->getTileWidth(), tilemaps[0]->getTileHeight());
	//explosionTex->setDstRect(position[0], position[1], tilemaps[0]->getTileWidth(), tilemaps[0]->getTileHeight());
	if (position[1] < -10)
	{
		Actor::destroy();
	}
}

void Missile::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	float velocityZero[2]{ 0.0f, 0.0f };
	rigidBody->setVelocity(velocityZero);
	animations[0]->stop();
	textures[0] = explosionTex;
	explosionAnim->play();
	explosionAnim->destroyAfterEnd(this);
	rigidBody->setEnabled(false);

    Enemy* enemy = nullptr;
	enemy = dynamic_cast <Enemy*> (otherSensor);
	if (enemy)
	{
        enemy->takeDamage(missileDamage);
	}
}

Missile::~Missile()
{

}
