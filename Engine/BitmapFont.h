#pragma once
#include <string>

#include "Texture.h"
#include "Tilemap.h"

class BitmapFont
{
public:
	BitmapFont();

	// Generate the font
	void buildFont(Texture* fontBitmap, int rows, int cols);

	void drawText(int x, int y, std::string text, class SceneViewer* v);

private:
	// The font texture
	Texture* bitmap;
	Tilemap* tilemap;

	// New Line space
	int newLine;
};
