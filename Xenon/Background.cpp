#include "Background.h"

Background::Background() {
	Texture* texture = new Texture("../graphics/galaxy2.bmp");
	textures.push_back(texture);
}

void Background::update(float deltaTime) {

}