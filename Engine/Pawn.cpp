#include "Pawn.h"
#include "Engine.h"
#include "GameController.h"

Pawn::Pawn(float x, float y) {
	xpos = x;
	ypos = y;
	moveSpeed = 100.0f;
	controller = new GameController();
}

Pawn::~Pawn()
{
	delete textures[0];
	delete controller;
}

void Pawn::update(float deltaTime)
{
	/* Update position */
	textures[0]->setDstRect(xpos, ypos, textures[0]->getSrcRect()->w, textures[0]->getSrcRect()->h);
}

void Pawn::moveRight(float x) {
	xpos += x;
}

void Pawn::moveUp(float y) {
	ypos -= y;
}
