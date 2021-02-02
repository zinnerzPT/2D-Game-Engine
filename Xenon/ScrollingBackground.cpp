#include "ScrollingBackground.h"


ScrollingBackground::ScrollingBackground(std::string filepath, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh, int offsetX, int offsetY, bool hFlip, bool vFlip, float speed, int resetOffset)
{
	Texture* texture = new Texture(filepath);
	if (sx)
	{
		//texture->setSrcRect(sx, sy, sw, sh);
		//texture->setDstRect(dx, dy, dw, dh);
	}
	textures.push_back(texture);

	additionalOffsetX = offsetX;
	additionalOffsetY = offsetY;
	flipHorizontal = hFlip;
	flipVertical = vFlip;
	scrollSpeed = speed;
	this->resetOffset = resetOffset;
}


void ScrollingBackground::update(float deltaTime)
{
	if (additionalOffsetX || additionalOffsetY)
	{
		frameTime += deltaTime;
		if (frameTime >= 0.05f / scrollSpeed)
		{
			frameTime = 0.0f;

			if (offset == resetOffset)
			{
				offset = 0;
			}
			offset++;
			//textures[0]->setTexOffset(additionalOffsetX, offset + additionalOffsetY);
		}
	}
}