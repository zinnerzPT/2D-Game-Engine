#include "Spaceship.h"

Spaceship::Spaceship(std::string filePath, int x, int y) :Pawn(filePath, x, y) {

}

void Spaceship::update(float deltaTime) {
	moveRight(1.0f);
	moveUp(1.0f);
}

//"../graphics/Ship1.bmp"