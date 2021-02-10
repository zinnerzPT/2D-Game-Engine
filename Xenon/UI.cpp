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

	// Set the rendering layer
	this->setLayer(5);
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

	drawText("Player One", smallFont, 8, 464);

	// convert scores to string with 10 digits
	char buffer[256];
	sprintf_s(buffer, "%010d", gameManager->getScore());
	std::string currentScore(buffer);
	drawText(currentScore, largeFont, 8, 444);

	sprintf_s(buffer, "%010d", gameManager->getHiScore());
	std::string hiScore(buffer);

	drawText(" Hi Score \n" + hiScore, smallFont, 280, 464);

	// Lives
	drawBar(gameManager->getLives(), livesBar, 8, 32, 0, 4);

	// Health bar
	int healthColor = (gameManager->getHealth() / 30.0f) - 0.34f;
	drawBar(gameManager->getHealth() / 5.0f, healthBar, 8, 8, healthColor, 1);
}