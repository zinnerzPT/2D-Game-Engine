#pragma once

#include <string>

class Texture
{
public:
	Texture(std::string filePath);

	inline struct SDL_Texture* GetTexture() { return texture; }

	inline float getPosOffsetX() { return posOffsetX; }
	inline float getPosOffsetY() { return posOffsetY; }

	/* Queries the width and height of the texture. */
	void query(int* w, int* h);

	void setRowsAndColumns(int rows, int columns);
	void queryWidthHeight(int* w, int* h);

	void setOffset(float x, float y);
	void setPosOffset(float x, float y);

	~Texture();

	void draw(class SceneViewer* v, class Transform* t = nullptr);

private:
	struct SDL_Texture* texture = nullptr;

	float offsetX = 0.0f;
	float offsetY = 0.0f;

	float posOffsetX = 0.0f;
	float posOffsetY = 0.0f;

	int width = 1;
	int height = 1;

	uint32_t textureID = -1;
	uint32_t vao = -1;
	uint32_t vbo = -1;
	//glm::vec2 textureOffset;
public:
	void setVertices(float sx, float sy, float sw, float sh);
};
