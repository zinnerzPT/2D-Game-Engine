#pragma once

#include "Texture.h"
#include "Tilemap.h"

#include <string>
#include <vector>
#include "BitmapFont.h"
#include "UIBar.h"

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
	void drawText(std::string text, BitmapFont* font, int x, int y);
	void drawBar(int length, UIBar* bar, int x, int y, int frame = 0, int padding = 0);
protected:
	std::vector<Texture*> textures;
	std::vector<Tilemap*> tilemaps;

	class Transform* transform;


};

