#pragma once

#include <SDL2/SDL.h>
#include <string>

class Texture
{
public:
	Texture(std::string filePath);

	SDL_Texture* GetTexture() { return texture; }

	SDL_Rect* getSrcRect();
	SDL_Rect* getDstRect();

	void setSrcRect(SDL_Rect newRect);
	void setSrcRect(int x, int y, int w, int h);
	void setDstRect(SDL_Rect newRect);
	void setDstRect(int x, int y, int w, int h);

	/* Queries the width and height of the texture. */
	void query(int* w, int* h);

	~Texture();

private:
	SDL_Texture* texture = nullptr;
	SDL_Rect* srcRect = NULL;
	SDL_Rect* dstRect = NULL;
};
