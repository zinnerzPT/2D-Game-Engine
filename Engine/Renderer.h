#pragma once

#include <SDL2/SDL.h>
#include "Window.h"
#include "Texture.h"

class Renderer
{
public:
	Renderer(Window* window);

	void clear();
	void copy(Texture* texture, Rect* rect, Rect* pos, bool horizontalFlip = false, bool verticalFlip = false);
	void present();

	SDL_Texture* createTextureFromSurface(SDL_Surface* surface);

	~Renderer();
private:
	SDL_Renderer* renderer;
};
