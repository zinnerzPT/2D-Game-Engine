#include "Tilemap.h"

Tilemap::Tilemap(std::string filepath, int r, int c, SDL_Renderer* renderTarget)
{

	SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
	if (surface == NULL)
		std::cout << "Error creating surface" << std::endl;
	else
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error creating texture" << std::endl;
	}
	SDL_FreeSurface(surface);

	// get the width and height of the tilemap
	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

	rows = r;
	columns = c;

	frameWidth = textureWidth / columns;
	frameHeight = textureHeight / rows;

	currentFrame.w = frameWidth;
	currentFrame.h = frameHeight;

	frameSize.w = frameWidth;
	frameSize.h = frameHeight;
}

Tilemap::~Tilemap()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void Tilemap::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &currentFrame, &frameSize);
}

void Tilemap::ChangeFrame(int frameNumber)
{
	if (frameNumber <= 0 || frameNumber > rows * columns)
	{
		std::cout << "Error: Invalid frame number" << std::endl;
	}
	else
	{
		currentFrame.x = frameWidth * ((frameNumber - 1) % columns);
		currentFrame.y = frameHeight * ((frameNumber - 1) / columns);

		// std::cout << "X: " << currentFrame.x << " Y: " << currentFrame.y << std::endl;
	}
}