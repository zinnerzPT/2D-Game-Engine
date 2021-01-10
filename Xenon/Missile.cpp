#include "Missile.h"
#include "RigidBody.h"

Missile::Missile(float position[2], float halfSize[2], float density, float linearVelocity[2]) : Projectile(position, halfSize, density, linearVelocity)
{
	Texture* texture = new Texture("../graphics/missile.bmp");
	textures.push_back(texture);

	tilemap = new Tilemap(texture, 3, 2);
	animation = new Animation(tilemap, { 0,1 }, true);
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
}

void Missile::onContact()
{
	float velocityZero[2]{ 0.0f, 0.0f };
	rigidBody->setVelocity(velocityZero);
	animation->stop();
	textures[0] = explosionTex;
	explosionAnim->play();
	explosionAnim->destroyAfterEnd(this);
	rigidBody->setEnabled(false);

}

Missile::~Missile()
{
	delete animation;
	delete explosionAnim;
}
