#pragma once

#include "Texture.h"
#include "Tilemap.h"

#include <string>
#include <vector>
#include "BitmapFont.h"

class UICanvas
{
public: 
	UICanvas();

	virtual void update(float deltaTime) = 0;
	virtual void draw(class SceneViewer* v = nullptr);
	void destroy();

	virtual ~UICanvas();

	inline class Transform* getTransform() { return transform; }
protected:
	void drawText(std::string text, BitmapFont* font, float x, float y);

protected:
	std::vector<Texture*> textures;
	std::vector<Tilemap*> tilemaps;

	class Transform* transform;


};

