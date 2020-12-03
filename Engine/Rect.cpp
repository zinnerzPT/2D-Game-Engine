#include "Rect.h"
#include <SDL2/SDL.h>

Rect::Rect()
{
	sdl_Rect = new SDL_Rect();

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
