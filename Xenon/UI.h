#pragma once

#include "Actor.h"
#include "BitmapFont.h"
#include "UIBar.h"

class UI : public Actor
{
public:
	UI(float x, float y);
	~UI();
	void update(float deltaTime);

	void render();

private:
	BitmapFont* smallFont;
	BitmapFont* largeFont;
	UIBar* livesBar;
	UIBar* healthBar;
};

