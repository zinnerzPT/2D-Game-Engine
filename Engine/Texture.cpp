#include "Texture.h"

#include <SDL2/SDL.h>

#include "InitError.h"
#include "Renderer.h"
#include "Engine.h"

Texture::Texture(std::string filePath)
{
	// Load image from specified path
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
	srcRect = new Rect();
	srcRect->w = w;
	srcRect->h = h;
	dstRect = new Rect();
	dstRect->w = w;
	dstRect->h = h;
}

Rect* Texture::getSrcRect()
{
	return srcRect;
}

Rect* Texture::getDstRect()
{
	Rect* rect = new Rect();
	return dstRect;
}

void Texture::setSrcRect(Rect newRect)
{
	srcRect->x = newRect.x;
	srcRect->y = newRect.y;
	srcRect->w = newRect.w;
	srcRect->h = newRect.h;
}

void Texture::setSrcRect(int x, int y, int w, int h)
{
	srcRect->x = x;
	srcRect->y = y;
	srcRect->w = w;
	srcRect->h = h;
}

void Texture::setDstRect(Rect newRect)
{
	// sets dstRect and keeps the texture offset
	dstRect->x = newRect.x + texOffsetX;
	dstRect->y = newRect.y + texOffsetY;
	dstRect->w = newRect.w;
	dstRect->h = newRect.h;
}

void Texture::setDstRect(int x, int y, int w, int h)
{
	// sets dstRect and keeps the texture offset
	dstRect->x = x + texOffsetX;
	dstRect->y = y + texOffsetY;
	dstRect->w = w;
	dstRect->h = h;
}

void Texture::setTexOffset(int x, int y)
{
	// remove the offset from the dstRect
	dstRect->x -= texOffsetX;
	dstRect->y -= texOffsetY;

	texOffsetX = x;
	texOffsetY = y;

	// add it back
	dstRect->x += texOffsetX;
	dstRect->y += texOffsetY;

	// this will make sure the offset is always applied
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
