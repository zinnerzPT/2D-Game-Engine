#include "Spaceship.h"

Spaceship::Spaceship(float x, float y) :Pawn(x, y) {
	texture = new Texture("../graphics/Ship1.bmp");
	tilemap = new Tilemap(texture, 1, 7);
	tilemap->ChangeFrame(3);
	animation = new Animation(tilemap, { 0,1,2,3,4,5,6,5,4,3,2,1 }, true);
	xpos = x;
	ypos = y;
	moveSpeed = 200.0f;
}

void Spaceship::update(float deltaTime) {

	Pawn::update(deltaTime);
}

void Spaceship::fire() {
	//Fire missiles
}
