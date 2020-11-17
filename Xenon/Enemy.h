#pragma once
#include "Actor.h"

#include "Tilemap.h"
#include "Animation.h"
#include "RigidBody.h"

class Enemy : public Actor
{
public:
	virtual void update(float deltaTime) = 0;

protected:
	Tilemap* tilemap = nullptr;
	Animation* animation = nullptr;
	RigidBody* rigidBody = nullptr;
};