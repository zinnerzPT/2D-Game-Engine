#include "UIBar.h"
#include "Engine.h"
#include "SceneViewer.h"
#include "Transform.h"

static Transform* pos;

UIBar::UIBar()
{
	//Initialize variables
	texture = nullptr;
	tilemap = nullptr;
	if (pos == nullptr)
		pos = new Transform;
}

void UIBar::buildBar(Texture* barBitmap, int rows, int cols)
{
	texture = barBitmap;
	tilemap = new Tilemap(barBitmap, rows, cols);
}

void UIBar::drawBar(int x, int y, int length, SceneViewer* v, int frame, int padding)
{
	if (texture != NULL) {
		// Sprite offsets
		pos->setPosition(x, y);
		int curX = x, curY = y;

		tilemap->ChangeFrame(frame);

		// Draw the bar
		for (int i = 0; i < length; ++i) {
			v->setModelMatrix(pos->getGlmTransform());
			texture->draw(v);

			//Move over the width of one character + padding
			pos->Translate(tilemap->getTileWidth() + padding, 0.0f);
			curX += tilemap->getTileWidth() + padding;
		}
	}
}
