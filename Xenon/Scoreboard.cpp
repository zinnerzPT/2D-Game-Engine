#include "Scoreboard.h"
#include "BitmapFont.h"

// this int is just for testing purposes
int i = 0;

Scoreboard::Scoreboard(float x, float y) {
	Texture* texture = new Texture("../graphics/font16x16.bmp");
	textures.push_back(texture);

	font = new BitmapFont();
	font->buildFont(texture, 12, 8);
	
}

void Scoreboard::update(float deltaTime) {
	i++;
}

void Scoreboard::render() {
	font->renderText(100, 100, "Test\nTest2 Test3\n" + std::to_string(i));
}