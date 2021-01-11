#pragma once

#include "Actor.h"
#include "RigidBody.h"

class Pawn : public Actor
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

	RigidBody* rigidBody = nullptr;
	float velocity[2]{ 0.0f, 0.0f };
};

