#pragma once

#include "UICanvas.h"
#include "BitmapFont.h"
#include "UIBar.h"

class UI : public UICanvas
{
public:
	UI();
	~UI();
	void update(float deltaTime);

	void draw(class SceneViewer* v) override;
private:
	BitmapFont* smallFont;
	BitmapFont* largeFont;
	UIBar* livesBar;
	UIBar* healthBar;
};

