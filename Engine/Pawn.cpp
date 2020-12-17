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
	delete texture;
	delete controller;
}

void Pawn::update(float deltaTime)
{
	/* Update position */
	texture->setDstRect(xpos, ypos, texture->getSrcRect()->w, texture->getSrcRect()->h);
}

void Pawn::moveRight(float x) {
	xpos += x;
}

void Pawn::moveUp(float y) {
	ypos -= y;
}
