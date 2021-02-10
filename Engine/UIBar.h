#pragma once

#include "Texture.h"
#include "Tilemap.h"

class UIBar
{

public:
	UIBar();

	// Generate the bar from sprites
	void buildBar(Texture* barBitmap, int rows, int cols);

	void drawBar(int x, int y, int length, class SceneViewer* v, int frame = 0, int padding = 0);


private:
	// The font texture
	Texture* texture;
	Tilemap* tilemap;
};

