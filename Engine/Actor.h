#pragma once

#include "Texture.h"
#include "Tilemap.h"
#include "Animation.h"
#include <string>

class Actor
{
public:
	Actor();
	//~Actor();

	virtual void update(float deltaTime) = 0;
	void render();

protected:
	float xpos = 0.0f;
	float ypos = 0.0f;
	Texture* texture = nullptr;
	Tilemap* tilemap = nullptr;
	Animation* animation = nullptr;
};
