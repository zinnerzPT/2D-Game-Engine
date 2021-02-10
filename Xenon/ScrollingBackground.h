#pragma once

#include "Actor.h"

class ScrollingBackground :
	public Actor
{
public:
	ScrollingBackground(std::string filepath, int topLeftX, int topLeftY, int width, int height, int x, int y, float speed, int layer = -5, int yReset = 0);
	void update(float deltaTime);

private:
	int h;
	int yReset;
	float scrollSpeed;
	float frameTime = 0;
};

