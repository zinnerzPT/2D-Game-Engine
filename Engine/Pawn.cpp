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
	for (Texture* t : textures)
	{
		//t->setDstRect(xpos, ypos, t->getSrcRect()->w, t->getSrcRect()->h);

		float* position;
		position = rigidBody->getPosition();
		xpos = position[0] = position[0] * 16.0f - tilemap->getTileWidth() / 2;
		ypos = position[1] = position[1] * 16.0f - tilemap->getTileHeight() / 2;
		t->setDstRect(position[0], position[1], t->getSrcRect()->w, t->getSrcRect()->h);
	}
}

void Pawn::moveRight(float x) 
{
	velocity[0] = x;
	if (rigidBody)
	{
		rigidBody->setVelocity(velocity);
	}
	//xpos += x;
}

void Pawn::moveUp(float y)
{
	velocity[1] = -y;
	if (rigidBody)
	{
		rigidBody->setVelocity(velocity);
	}
	//ypos -= y;
}
