#include "Texture.h"

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "InitError.h"
#include "Renderer.h"
#include "Engine.h"

GLuint tex;

Texture::Texture(std::string filePath)
{
	// Load image from specified path
	SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
	if (surface == NULL)
		throw InitError();
	else
	{
		//SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
		//texture = Engine::renderer->createTextureFromSurface(surface);


		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_BGR,
			GL_UNSIGNED_BYTE, surface->pixels);
		//glGenerateMipmap(GL_TEXTURE_2D);


		/*if (texture == NULL)
			throw InitError();*/
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




	SDL_Surface* image = SDL_LoadBMP("../graphics/Ship1.bmp");
	if (image != NULL)
	{
		
	}
	SDL_FreeSurface(image);
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
