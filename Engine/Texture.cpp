#include "Texture.h"
#include "InitError.h"
#include "Renderer.h"

Texture::Texture(std::string filePath, Renderer* renderer)
{
	texture = nullptr;
	SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
	if (surface == NULL)
		throw InitError();
	else
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
		texture = renderer->createTextureFromSurface(surface);
		if (texture == NULL)
			throw InitError();
	}

	SDL_FreeSurface(surface);
}

void Texture::query(int* w, int* h)
{
	SDL_QueryTexture(texture, NULL, NULL, w, h);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}
