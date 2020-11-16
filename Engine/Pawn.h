#pragma once
#include "Actor.h"
class Pawn :
    public Actor
{
public:
	Pawn(std::string filePath, float x, float y);
	//Pawn(std::string textureFilePath, Renderer renderer);

	~Pawn();

	void update(float deltaTime);
	void moveRight(float x);
	void moveUp(float y);
protected:
	float moveSpeed;
};

