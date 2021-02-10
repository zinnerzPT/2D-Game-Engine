#include "BitmapFont.h"
#include "Engine.h"
#include <glm/glm.hpp>
#include "Transform.h"
#include "SceneViewer.h"

static Transform* pos;

BitmapFont::BitmapFont()
{
	//Initialize variables
	bitmap = nullptr;
	tilemap = nullptr;
	newLine = 0;
	if (pos == nullptr)
		pos = new Transform;
}

void BitmapFont::buildFont(Texture* fontBitmap, int rows, int cols)
{
	bitmap = fontBitmap;
	tilemap = new Tilemap(fontBitmap, rows, cols);

	// Set new line to slightly taller than a character
	newLine = -(tilemap->getTileHeight() + 1);
}

void BitmapFont::drawText(int x, int y, std::string text, SceneViewer* v)
{
	// If the bitmap has been built
	if (bitmap != NULL) {
		// Character offsets
		pos->setPosition(x, y);
		int curX = x, curY = y;

		// Go through the text
		for (int i = 0; i < text.length(); ++i) {
			// If the current character is a newline
			if (text[i] == '\n') {
				// Move down and back
				pos->Translate(x - curX, newLine);
				curY += newLine;
				curX += x - curX;
			}
			else {
				// Get the ASCII value of the character minus 32 because we don't have the first 32 characters
				int ascii = text[i] - 32;
				tilemap->ChangeFrame(ascii);

				// Render the character
				v->setModelMatrix(pos->getGlmTransform());
				bitmap->draw(v);

				//Move over the width of one character + 1 for padding
				pos->Translate(tilemap->getTileWidth(), 0.0f);
				curX += tilemap->getTileWidth();
			}
		}
	}
}
