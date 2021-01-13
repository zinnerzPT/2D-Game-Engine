#include "Scoreboard.h"
#include "BitmapFont.h"
#include <string>

// this int is just for testing purposes
int i = 0;
int score = 0;

Scoreboard::Scoreboard(float x, float y) {
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

Scoreboard::~Scoreboard()
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

void Scoreboard::update(float deltaTime) {
	++i;
	if (i >= 60) {
		score += 150;
		i = 0;
	}
}

void Scoreboard::render() {
	smallFont->renderText(10, 10, "Player One");
	smallFont->renderText(300, 10, " Hi Score \n0002000000");

	// convert score to string with 10 digits
	char buffer[256];
	sprintf_s(buffer, "%010d", score);
	std::string currentScore(buffer);

	largeFont->renderText(10, 20, currentScore);

	livesBar->renderBar(10, 410, 3,0,4);
	healthBar->renderBar(10, 450, 20, 2, 1);
}