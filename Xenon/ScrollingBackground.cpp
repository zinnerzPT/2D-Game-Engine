#include "ScrollingBackground.h"

ScrollingBackground::ScrollingBackground(std::string filepath, int topLeftX, int topLeftY, int width, int height, int x, int y, float speed, int layer, int yReset) :Actor(x, y)
{
	Texture* texture = new Texture(filepath);

	textures.push_back(texture);

	scrollSpeed = speed;
	xpos = x;
	ypos = y;
	h = height;
	this->yReset = yReset;

	this->setLayer(layer);
	texture->setVertices(topLeftX, topLeftY, width, height);
}

void ScrollingBackground::update(float deltaTime)
{

	frameTime += deltaTime;
	if (frameTime >= 0.05f / scrollSpeed)
	{
		frameTime = 0.0f;

		if (ypos <= -(h + yReset))
		{
			ypos = 512;
		}
		ypos--;
	}
}