#include "UIBar.h"
#include "Engine.h"
#include "Renderer.h"

UIBar::UIBar()
{
	//Initialize variables
	texture = nullptr;
	tilemap = nullptr;
}

void UIBar::buildBar(Texture* barBitmap, int rows, int cols)
{
	texture = barBitmap;
	tilemap = new Tilemap(barBitmap, rows, cols);

	// Set new line to slightly taller than a character
	//newLine = tilemap->getTileHeight() + 1;
}

void UIBar::renderBar(int x, int y, int length, int frame, int padding)
{
	if (texture != NULL) {
		// Sprite offsets
		int curX = x, curY = y;

		tilemap->ChangeFrame(frame);

		// Draw the bar
		for (int i = 0; i < length; ++i) {

			texture->setDstRect(curX, curY, texture->getDstRect()->w, texture->getDstRect()->h);
			Engine::renderer->copy(texture, texture->getSrcRect(), texture->getDstRect());

			//Move over the width of one character + 1 for padding
			curX += tilemap->getTileWidth() + padding;
		}
	}
}
