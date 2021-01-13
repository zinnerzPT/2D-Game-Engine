#pragma once

#include "Actor.h"

class ScrollingBackground :
	public Actor
{
public:
	ScrollingBackground(std::string filepath, int sx = 0, int sy = 0, int sw = 0, int sh = 0,
		int dx = 0, int dy = 0, int dw = 0, int dh = 0, int offsetX = 0, int offsetY = 0, bool hFlip = false, bool vFlip = false, float speed = 1.0f, int resetOffset = 512);
	void update(float deltaTime);

private:
	int offset = 0;
	int additionalOffsetX = 0;
	int additionalOffsetY = 0;
	float scrollSpeed;
	int resetOffset;
	float frameTime = 0;
};

