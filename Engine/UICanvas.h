#pragma once

#include "Texture.h"
#include "Tilemap.h"

#include <string>
#include <vector>

class UICanvas
{
public: 
	UICanvas();

	virtual void update(float deltaTime) = 0;
	virtual void render();
	void destroy();

	virtual ~UICanvas();

protected:
	std::vector<Texture*> textures;
	std::vector<Tilemap*> tilemaps;
};

