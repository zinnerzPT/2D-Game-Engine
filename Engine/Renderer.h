#pragma once

#include <SDL2/SDL.h>
#include "Window.h"
#include "Texture.h"

class Renderer
{
public:
	Renderer(Window* window);

	void clear();
	void copy(Texture* texture, SDL_Rect* rect, SDL_Rect* pos);
	void present();

	SDL_Texture* createTextureFromSurface(SDL_Surface* surface);

	~Renderer();
private:
	SDL_Renderer* renderer;
};
