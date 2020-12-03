#pragma once

#include "Rect.h"
#include <string>

class Texture
{
public:
	Texture(std::string filePath);

	struct SDL_Texture* GetTexture() { return texture; }

	Rect* getSrcRect();
	Rect* getDstRect();

	void setSrcRect(Rect newRect);
	void setSrcRect(int x, int y, int w, int h);
	void setDstRect(Rect newRect);
	void setDstRect(int x, int y, int w, int h);

	/* Queries the width and height of the texture. */
	void query(int* w, int* h);

	~Texture();

private:
	struct SDL_Texture* texture = nullptr;
	Rect* srcRect = NULL;
	Rect* dstRect = NULL;
};
