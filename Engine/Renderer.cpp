#include "Renderer.h"

Renderer::Renderer(Window* window)
{
	renderer = SDL_CreateRenderer(window->getWindow(), -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
}

void Renderer::clear()
{
	SDL_RenderClear(renderer);
}

void Renderer::copy(Texture* texture, SDL_Rect* rect, SDL_Rect* pos)
{
	SDL_RenderCopy(renderer, texture->GetTexture(), rect, pos);
}

void Renderer::present()
{
	SDL_RenderPresent(renderer);
}

SDL_Texture* Renderer::createTextureFromSurface(SDL_Surface* surface)
{
	return SDL_CreateTextureFromSurface(renderer, surface);
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}
