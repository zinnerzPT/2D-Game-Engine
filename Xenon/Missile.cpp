#include "Missile.h"
#include "RigidBody.h"
#include "Enemy.h"

Missile::Missile(float position[2], float halfSize[2], float density, float linearVelocity[2], uint16_t categoryBits, uint16_t maskBits, MissileType type)
	: Projectile(position, halfSize, density, linearVelocity, categoryBits, maskBits)
{
	Texture* texture = new Texture("../graphics/missile.bmp");
	textures.push_back(texture);

	tilemap = new Tilemap(texture, 3, 2);
	switch (type)
	{
	case MissileType::light:
		animation = new Animation(tilemap, { 0,1 }, true);
		missileDamage = lightDamage;
		break;
	case MissileType::medium:
		tilemap->ChangeFrame(2);
		animation = new Animation(tilemap, { 2,3 }, true);
		missileDamage = mediumDamage;
		break;
	case MissileType::heavy:
		tilemap->ChangeFrame(4);
		animation = new Animation(tilemap, { 4,5 }, true);
		missileDamage = heavyDamage;
		break;
	}
	animation->play();

	explosionTex = new Texture("../graphics/explode16.bmp");
	explosionTilemap = new Tilemap(explosionTex, 2, 5);
	explosionAnim = new Animation(explosionTilemap, { 0,1,2,3,4,5,6,7,8,9 }, false);
}

void Missile::update(float deltaTime)
{
	float* position;
	position = rigidBody->getPosition();
	position[0] = position[0] * 16.0f - tilemap->getTileWidth() / 2;
	position[1] = position[1] * 16.0f - tilemap->getTileHeight() / 2;
	textures[0]->setDstRect(position[0], position[1], tilemap->getTileWidth(), tilemap->getTileHeight());
	explosionTex->setDstRect(position[0], position[1], tilemap->getTileWidth(), tilemap->getTileHeight());
	if (position[1] < -10)
	{
		Actor::destroy();
	}
}

void Missile::onContact(ContactSensor* otherSensor /*= nullptr*/)
{
	float velocityZero[2]{ 0.0f, 0.0f };
	rigidBody->setVelocity(velocityZero);
	animation->stop();
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
	delete animation;
	delete explosionAnim;
}
