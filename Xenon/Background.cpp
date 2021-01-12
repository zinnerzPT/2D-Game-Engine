#include "Background.h"

Background::Background(std::string filepath, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh, int offsetX, int offsetY)
{
	Texture* texture = new Texture(filepath);
	if (sx)
	{
		texture->setSrcRect(sx, sy, sw, sh);
		texture->setDstRect(dx, dy, dw, dh);
	}
	textures.push_back(texture);

	additionalOffsetX = offsetX;
	additionalOffsetY = offsetY;
}


void Background::update(float deltaTime)
{
	if (additionalOffsetX || additionalOffsetY)
	{
		frameTime += deltaTime;
		if (frameTime >= 0.01f)
		{
			frameTime = 0;

			if (offset == 512)
			{
				offset = 0;
			}
			offset++;
			textures[0]->setTexOffset(additionalOffsetX, offset + additionalOffsetY);
		}
	}

}