#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include "Texture.h"

class Tilemap
{
public:
	Tilemap(Texture* tex, int r, int c);
	void ChangeFrame(int frameNumber);

	int getTileWidth();
	int getTileHeight();

private:
	int rows = 0;
	int columns = 0;
	int textureWidth = 0;
	int textureHeight = 0;
	int tileWidth = 0;
	int tileHeight = 0;

	SDL_Rect currentFrame;
	SDL_Rect tileSize;

	Texture* texture;
};

