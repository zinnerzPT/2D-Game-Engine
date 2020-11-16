#pragma once
#include "Actor.h"
class Pawn :
    public Actor
{
public:
	Pawn(std::string filePath, int x, int y);
	//Pawn(std::string textureFilePath, Renderer renderer);

	~Pawn();

	void update(float deltaTime);
	void moveRight(float x);
	void moveUp(float y);
	void render();
private:
	int textureWidth;
	int textureHeight;

	int frameWidth, frameHeight;
};

