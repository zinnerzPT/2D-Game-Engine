#pragma once

#include "UICanvas.h"
#include "BitmapFont.h"
#include "UIBar.h"

class UI : public UICanvas
{
public:
	UI(float x, float y);
	~UI();
	void update(float deltaTime);

	void render() override;

private:
	BitmapFont* smallFont;
	BitmapFont* largeFont;
	UIBar* livesBar;
	UIBar* healthBar;
};

