#pragma once
#include <SDL2/SDL.h>
#include <string>

class Texture
{
public:
	Texture(std::string filePath, class Renderer* renderer);

	SDL_Texture* GetTexture() { return texture; }

	void query(int* w, int* h);

	~Texture();

private:
	SDL_Texture* texture;
};
