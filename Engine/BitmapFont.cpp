#include "BitmapFont.h"
#include "Engine.h"
#include "Renderer.h"

BitmapFont::BitmapFont()
{
	//Initialize variables
	bitmap = NULL;
	newLine = 0;
}

void BitmapFont::buildFont(Texture* fontBitmap, int rows, int cols)
{
	bitmap = fontBitmap;
	tilemap = new Tilemap(fontBitmap, rows, cols);

	// Set new line to slightly taller than a character
	newLine = tilemap->getTileHeight() + 1;
}

void BitmapFont::renderText(int x, int y, std::string text)
{
	// If the bitmap has been built
	if (bitmap != NULL) {
		// Character offsets
		int curX = x, curY = y;
		
		// Go through the text
		for (int i = 0; i < text.length(); ++i) {
			// If the current character is a newline
			if (text[i] == '\n') {
				// Move down
				curY += newLine;

				// And back
				curX = x;
			}
			else {
				// Get the ASCII value of the character minus 32 because we don't have the first 32 characters
				int ascii = text[i]-32;

				// Render the character
				tilemap->ChangeFrame(ascii);
				bitmap->setDstRect(curX, curY, bitmap->getDstRect()->w, bitmap->getDstRect()->h);
				Engine::renderer->copy(bitmap, bitmap->getSrcRect(), bitmap->getDstRect());

				//Move over the width of one character + 1 for padding
				curX += tilemap->getTileWidth() + 1;
			}
		}
	}
}
