#include "Rect.h"
#include <SDL2/SDL.h>

Rect::Rect(int x, int y, int w, int h)
{
	sdl_Rect = new SDL_Rect();
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	sdl_Rect->x = x;
	sdl_Rect->y = y;
	sdl_Rect->w = w;
	sdl_Rect->h = h;
}

Rect::~Rect()
{
	//delete sdl_Rect;
}

SDL_Rect* Rect::toSDL_Rect()
{
	sdl_Rect->x = x;
	sdl_Rect->y = y;
	sdl_Rect->w = w;
	sdl_Rect->h = h;
	return sdl_Rect;
}
