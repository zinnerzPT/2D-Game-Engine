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
	moveRight(1.0f);
	moveUp(-1.0f);

	/*texture->getSrcRect()->h = 32;
	texture->getSrcRect()->w = 32;
	texture->getSrcRect()->x = 0;
	texture->getSrcRect()->y = 0;*/

	texture->setDstRect(xpos, ypos, texture->getSrcRect()->w, texture->getSrcRect()->h);
	/*texture->getDstRect()->x = xpos;
	texture->getDstRect()->y = ypos;
	texture->getDstRect()->w = texture->getSrcRect()->w;
	texture->getDstRect()->h = texture->getSrcRect()->h;*/
}

void Pawn::moveRight(float x) {
	xpos += x;
}

void Pawn::moveUp(float y) {
	ypos -= y;
}
