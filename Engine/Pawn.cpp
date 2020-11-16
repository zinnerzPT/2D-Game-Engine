#include "Pawn.h"
#include "Engine.h"
#include <iostream>

Pawn::Pawn(float x, float y) {
	xpos = x;
	ypos = y;
	moveSpeed = 100.0f;
}

Pawn::~Pawn()
{
	delete texture;
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
