#include "Renderer.h"

Renderer::Renderer(Window* window)
{
	renderer = SDL_CreateRenderer(window->getWindow(), -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
}

void Renderer::clear()
{
	SDL_RenderClear(renderer);
}

void Renderer::copy(Texture* texture, Rect* rect, Rect* pos, bool horizontalFlip, bool verticalFlip)
{
	SDL_RendererFlip flip = (SDL_RendererFlip)NULL;
	if (horizontalFlip)
		flip = (SDL_RendererFlip)(flip | SDL_FLIP_HORIZONTAL);
	if(verticalFlip)
		flip = (SDL_RendererFlip)(flip |SDL_FLIP_VERTICAL);
	//SDL_RenderCopy(renderer, texture->GetTexture(), rect->toSDL_Rect(), pos->toSDL_Rect());
	SDL_RenderCopyEx(renderer, texture->GetTexture(), rect->toSDL_Rect(), pos->toSDL_Rect(), 0, NULL, flip);
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
