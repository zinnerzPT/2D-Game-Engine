#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Tilemap
{
public:
	Tilemap(std::string filepath, int rows, int columns, SDL_Renderer* renderTarget);
	~Tilemap();
	void Draw(SDL_Renderer* renderTarget);
	void ChangeFrame(int frameNumber);

private:
	SDL_Texture* texture = nullptr;

	int rows = 0;
	int columns = 0;
	int textureWidth = 0;
	int textureHeight = 0;
	int frameWidth = 0;
	int frameHeight = 0;

	SDL_Rect currentFrame;
	SDL_Rect frameSize;
};

