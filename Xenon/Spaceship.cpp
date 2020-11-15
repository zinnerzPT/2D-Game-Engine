#include "Spaceship.h"

Spaceship::Spaceship(std::string filePath, Renderer* renderer, int x, int y) :Pawn(filePath, renderer, x, y) {

}

void Spaceship::update(float deltaTime) {
	moveRight(1.0f);
	moveUp(1.0f);
}

//"../graphics/Ship1.bmp"