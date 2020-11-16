#pragma once
#include <SDL2/SDL.h>
#include <string>

class Texture
{
public:
	Texture(std::string filePath);

	SDL_Texture* GetTexture() { return texture; }

	/* Queries the width and height of the texture. */
	void query(int* w, int* h);

	~Texture();

private:
	SDL_Texture* texture;
};
