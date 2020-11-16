#pragma once
#include "Actor.h"

#include "Tilemap.h"
#include "Animation.h"

class Enemy : public Actor
{
public:
	Enemy();
	void update(float deltaTime);

private:
	Tilemap* tilemap;
	Animation* animation;

};