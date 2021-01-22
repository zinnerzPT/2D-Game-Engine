#pragma once

#include "Rect.h"
#include <string>

class Texture
{
public:
	Texture(std::string filePath);

	inline struct SDL_Texture* GetTexture() { return texture; }

	Rect* getSrcRect();
	Rect* getDstRect();

	void setSrcRect(Rect newRect);
	void setSrcRect(int x, int y, int w, int h);
	void setDstRect(Rect newRect);
	void setDstRect(int x, int y, int w, int h);
	void setTexOffset(int x, int y);

	/* Queries the width and height of the texture. */
	void query(int* w, int* h);

	inline uint32_t getTextureID() { return textureID; }
	inline uint32_t getVAO() { return vao; }
	void setRowsAndColumns(int rows, int columns);
	void queryWidthHeight(int* w, int* h);
	inline int getOffsetX() { return offsetX; }
	inline int getOffsetY() { return offsetY; }
	void setOffset(int x, int y);

	~Texture();

private:
	struct SDL_Texture* texture = nullptr;
	Rect* srcRect = NULL;
	Rect* dstRect = NULL;

	int texOffsetX = 0;
	int texOffsetY = 0;

	int offsetX = 0;
	int offsetY = 0;

	int width = 1;
	int height = 1;

	uint32_t textureID = -1;
	uint32_t vao = -1;
	uint32_t vbo = -1;
	//glm::vec2 textureOffset;
};
