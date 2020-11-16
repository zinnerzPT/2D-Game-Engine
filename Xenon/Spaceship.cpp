#include "Spaceship.h"

Spaceship::Spaceship(std::string filePath, float x, float y) :Pawn(filePath, x, y) {

}

void Spaceship::update(float deltaTime) {
	moveRight(1.0f);
	moveUp(1.0f);
}

//"../graphics/Ship1.bmp"