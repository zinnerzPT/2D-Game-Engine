#include "Pawn.h"
#include <iostream>

Pawn::Pawn(std::string filePath, Renderer* renderer, int x, int y) : Actor(x,y) {

	this->renderer = renderer;
	texture = new Texture(filePath, renderer);

	xpos = x;
	ypos = y;

	texture->query(&textureWidth, &textureHeight);

	frameWidth = textureWidth / 8;
	frameHeight = textureHeight / 2;

	srcRect.x = srcRect.y = 0;
	srcRect.w = frameWidth;
	srcRect.h = frameHeight;
}

Pawn::~Pawn()
{
	delete texture;
}

void Pawn::update(float deltaTime)
{
	moveRight(1.0f);
	moveUp(-1.0f);

	/*srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;*/

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void Pawn::moveRight(float x) {
	xpos += x;
}

void Pawn::moveUp(float y) {
	ypos -= y;
}

void Pawn::render()
{
	renderer->copy(texture, &srcRect, &destRect);
}
