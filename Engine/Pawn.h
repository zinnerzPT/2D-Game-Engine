#pragma once
#include "Actor.h"
class Pawn :
    public Actor
{
public:
	Pawn(std::string filePath, Renderer* renderer);
	//Pawn(std::string textureFilePath, Renderer renderer);
	~Pawn();

	void update(float deltaTime);
	void render();
private:
	int textureWidth;
	int textureHeight;

	int frameWidth, frameHeight;
};

