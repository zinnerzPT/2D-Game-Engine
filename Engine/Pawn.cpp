#include "Pawn.h"

Pawn::Pawn(std::string filePath, Renderer* renderer) {
	this->renderer = renderer;
	texture = new Texture(filePath, renderer);
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
	xpos = 0;
	ypos = 0;

	/*srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;*/

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void Pawn::render()
{
	renderer->copy(texture, &srcRect, &destRect);
}
