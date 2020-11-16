#include "Enemy.h"

Enemy::Enemy()
{
	texture = new Texture("../graphics/drone.bmp");
	tilemap = new Tilemap(texture, 2, 8);
	animation = new Animation(tilemap, { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 }, true);
}

void Enemy::update(float deltaTime) {
}