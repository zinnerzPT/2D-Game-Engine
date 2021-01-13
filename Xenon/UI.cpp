#include "UI.h"
#include "BitmapFont.h"
#include "GameManager.h"
#include <string>

UI::UI(float x, float y) {
	// Create fonts for the scoreboard
	Texture* smallTexture = new Texture("../graphics/font8x8.bmp");
	textures.push_back(smallTexture);

	Texture* largeTexture = new Texture("../graphics/font16x16.bmp");
	textures.push_back(largeTexture);

	smallFont = new BitmapFont();
	smallFont->buildFont(smallTexture, 15, 8);

	largeFont = new BitmapFont();
	largeFont->buildFont(largeTexture, 12, 8);

	// Create textures for the UI bars

	Texture* livesTexture = new Texture("../graphics/PULife.bmp");
	textures.push_back(livesTexture);

	livesBar = new UIBar();
	livesBar->buildBar(livesTexture, 1, 1);

	Texture* healthTexture = new Texture("../graphics/healthBar.bmp");
	textures.push_back(healthTexture);

	healthBar = new UIBar();
	healthBar->buildBar(healthTexture, 1, 3);
}

UI::~UI()
{
	delete smallFont;
	delete largeFont;

	delete livesBar;
	delete healthBar;

	for (Texture* t : textures)
	{
		delete t;
	}
}

void UI::update(float deltaTime) {

}

void UI::render() {
	smallFont->renderText(10, 10, "Player One");

	// convert scores to string with 10 digits
	char buffer[256];
	sprintf_s(buffer, "%010d", GameManager::getInstance()->getScore());
	std::string currentScore(buffer);
	largeFont->renderText(10, 20, currentScore);

	sprintf_s(buffer, "%010d", GameManager::getInstance()->getHiScore());
	std::string hiScore(buffer);

	smallFont->renderText(300, 10, " Hi Score \n" + hiScore);

	livesBar->renderBar(10, 410, GameManager::getInstance()->getLives(), 0, 4);

	int healthColor = (GameManager::getInstance()->getHealth() / 30.0f) - 0.34f;
	healthBar->renderBar(10, 450, GameManager::getInstance()->getHealth() / 5.0f, healthColor, 1);
}