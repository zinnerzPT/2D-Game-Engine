#include "Scoreboard.h"
#include "BitmapFont.h"
#include <string>

// this int is just for testing purposes
int i = 0;
int score = 0;

Scoreboard::Scoreboard(float x, float y) {
	Texture* smallTexture = new Texture("../graphics/font8x8.bmp");
	textures.push_back(smallTexture);

	Texture* largeTexture = new Texture("../graphics/font16x16.bmp");
	textures.push_back(largeTexture);

	smallFont = new BitmapFont();
	smallFont->buildFont(smallTexture, 15, 8);

	largeFont = new BitmapFont();
	largeFont->buildFont(largeTexture, 12, 8);
}

Scoreboard::~Scoreboard()
{
	delete smallFont;
	delete largeFont;

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
}