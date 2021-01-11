#pragma once

#include "Actor.h"
#include "BitmapFont.h"

class Scoreboard : public Actor
{
public:
	Scoreboard(float x, float y);
	void update(float deltaTime);

	void render();

private:
	BitmapFont* font;
};

