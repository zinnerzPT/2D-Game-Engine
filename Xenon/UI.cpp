#include "UI.h"
#include "BitmapFont.h"
#include "GameManager.h"
#include <string>

UI::UI() {
	// Create fonts for the scoreboard
	Texture* smallTexture = new Texture("../graphics/font8x8.bmp");
	textures.push_back(smallTexture);

	Texture* largeTexture = new Texture("../graphics/font16x16.bmp");
	textures.push_back(largeTexture);

	smallFont = new BitmapFont();
	smallFont->buildFont(smallTexture, 16, 8);

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
}

void UI::update(float deltaTime) {

}

void UI::draw(SceneViewer* v) {
	GameManager* gameManager = GameManager::getInstance();

	//drawText("1\n2\n3", smallFont, 100, 100);
	drawText("Player One", smallFont, 10, 460);

	// convert scores to string with 10 digits
	char buffer[256];
	sprintf_s(buffer, "%010d", gameManager->getScore());
	std::string currentScore(buffer);
	drawText(currentScore, largeFont, 10, 442);

	sprintf_s(buffer, "%010d", gameManager->getHiScore());
	std::string hiScore(buffer);

	//smallFont->renderText(300, 10, " Hi Score \n" + hiScore);
	drawText(" Hi Score \n" + hiScore, smallFont, 280, 460);

	//drawBar(gameManager->getLives(), livesBar, 10, 100);
	//livesBar->renderBar(10, 410, gameManager->getLives(), 0, 4);

	int healthColor = (gameManager->getHealth() / 30.0f) - 0.34f;
	drawBar(gameManager->getHealth() / 5.0f, healthBar, 10, 10, healthColor, 1);
	//healthBar->renderBar(10, 450, gameManager->getHealth() / 5.0f, healthColor, 1);
}