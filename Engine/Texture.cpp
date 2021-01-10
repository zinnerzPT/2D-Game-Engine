#include "Texture.h"

#include <SDL2/SDL.h>

#include "InitError.h"
#include "Renderer.h"
#include "Engine.h"

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
	rect->x = dstRect->x + texOffsetX;
	rect->y = dstRect->y + texOffsetY;
	rect->w = dstRect->w;
	rect->h = dstRect->h;

	return rect;
}

void Texture::setSrcRect(Rect newRect)
{
	if (srcRect == NULL || &newRect == NULL)
	{
		srcRect = new Rect();
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

void Texture::setDstRect(Rect newRect)
{
	if (dstRect == NULL || &newRect == NULL)
	{
		dstRect = new Rect();
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

void Texture::setTexOffset(int x, int y)
{
	texOffsetX = x;
	texOffsetY = y;
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
