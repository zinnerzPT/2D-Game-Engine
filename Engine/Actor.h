#pragma once

#include "Texture.h"
#include "Tilemap.h"

#include <string>
#include <vector>

class Animation;

class Actor
{
public:
	Actor();

	virtual void update(float deltaTime) = 0;
	virtual void render(class SceneViewer* v = nullptr);

	virtual ~Actor();

protected:
	float xpos = 0.0f;
	float ypos = 0.0f;
	std::vector<Texture*> textures;
	Tilemap* tilemap = nullptr;
	Animation* animation = nullptr;
};
