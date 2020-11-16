#include "Texture.h"
#include "InitError.h"
#include "Renderer.h"
#include "Engine.h"

// REMOVE THIS
#include <iostream>

Texture::Texture(std::string filePath)
{
	SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
	if (surface == NULL)
		throw InitError();
	else
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
		texture = Engine::renderer->createTextureFromSurface(surface);
		if (texture == NULL)
			throw InitError();
	}

	SDL_FreeSurface(surface);

	int w, h;
	query(&w, &h);
	dstRect = new SDL_Rect();
	dstRect->w = w;
	dstRect->h = h;

	std::cout << "Created Texture" << std::endl;
}

SDL_Rect* Texture::getSrcRect()
{
	return srcRect;
}

SDL_Rect* Texture::getDstRect()
{
	return dstRect;
}

void Texture::setSrcRect(SDL_Rect newRect)
{
	if (srcRect == NULL || &newRect == NULL)
	{
		srcRect = new SDL_Rect();
		srcRect->x = srcRect->y = srcRect->w = srcRect->h = 0;
	}
	*srcRect = newRect;
}

void Texture::setSrcRect(int x, int y, int w, int h)
{
	srcRect->x = x;
	srcRect->y = y;
	srcRect->w = w;
	srcRect->h = h;
}

void Texture::setDstRect(SDL_Rect newRect)
{
	if (dstRect == NULL || &newRect == NULL)
	{
		dstRect = new SDL_Rect();
		dstRect->x = dstRect->y = dstRect->w = dstRect->h = 0;
	}
	*dstRect = newRect;
}

void Texture::setDstRect(int x, int y, int w, int h)
{
	dstRect->x = x;
	dstRect->y = y;
	dstRect->w = w;
	dstRect->h = h;
}

void Texture::query(int* w, int* h)
{
	SDL_QueryTexture(texture, NULL, NULL, w, h);
}

Texture::~Texture()
{
	delete srcRect;
	delete dstRect;
	SDL_DestroyTexture(texture);
}
