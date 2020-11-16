#include "Tilemap.h"

Tilemap::Tilemap(Texture* tex, int r, int c)
{
	texture = tex;
	texture->query(&textureWidth, &textureHeight);
	
	rows = r;
	columns = c;

	tileWidth = textureWidth / columns;
	tileHeight = textureHeight / rows;

	currentFrame.w = tileWidth;
	currentFrame.h = tileHeight;

	tileSize.w = tileWidth;
	tileSize.h = tileHeight;

	texture->setSrcRect(currentFrame);
	texture->setDstRect(tileSize);
}

void Tilemap::ChangeFrame(int frameNumber)
{
	if (frameNumber <= 0 || frameNumber > rows * columns)
	{
		std::cout << "Error: Invalid frame number" << std::endl;
	}
	else
	{
		currentFrame.x = tileWidth * ((frameNumber - 1) % columns);
		currentFrame.y = tileHeight * ((frameNumber - 1) / columns);
		texture->setSrcRect(currentFrame);

		// std::cout << "X: " << currentFrame.x << " Y: " << currentFrame.y << std::endl;
	}
}

int Tilemap::getTileWidth()
{
	return tileWidth;
}

int Tilemap::getTileHeight()
{
	return tileHeight;
}

