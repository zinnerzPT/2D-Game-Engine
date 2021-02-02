#pragma once

#include <string>

class Texture
{
public:
	Texture(std::string filePath);

	inline struct SDL_Texture* GetTexture() { return texture; }

	void setTexOffset(int x, int y);

	/* Queries the width and height of the texture. */
	void query(int* w, int* h);

	/* Acho que estes 4 getters não são precisos
	inline uint32_t getTextureID() { return textureID; }
	inline uint32_t getVAO() { return vao; }
	inline float getOffsetX() { return offsetX; }
	inline float getOffsetY() { return offsetY; }*/

	void setRowsAndColumns(int rows, int columns);
	void queryWidthHeight(int* w, int* h);

	void setOffset(float x, float y);

	~Texture();

	void draw(class SceneViewer* v);

private:
	struct SDL_Texture* texture = nullptr;

	int texOffsetX = 0;
	int texOffsetY = 0;

	float offsetX = 0.0f;
	float offsetY = 0.0f;

	int width = 1;
	int height = 1;

	uint32_t textureID = -1;
	uint32_t vao = -1;
	uint32_t vbo = -1;
	//glm::vec2 textureOffset;
};
