#pragma once
#include "Actor.h"
#include "GameController.h"
class Pawn :
    public Actor
{
public:
	Pawn(float x, float y);
	//Pawn(std::string textureFilePath, Renderer renderer);

	~Pawn();

	void update(float deltaTime);
	void moveRight(float x);
	void moveUp(float y);

protected:
	float moveSpeed;
	class GameController* controller;
};

