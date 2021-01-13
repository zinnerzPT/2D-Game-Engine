#pragma once

#include "Actor.h"
#include "BitmapFont.h"
#include "UIBar.h"

class Scoreboard : public Actor
{
public:
	Scoreboard(float x, float y);
	~Scoreboard();
	void update(float deltaTime);

	void render();

private:
	BitmapFont* smallFont;
	BitmapFont* largeFont;
	UIBar* livesBar;
	UIBar* healthBar;
};

