#include "Texture.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "InitError.h"
#include "Engine.h"
#include "SceneViewer.h"
#include "Transform.h"

Texture::Texture(std::string filePath)
{
	// Load image from specified path
	SDL_Surface* image = SDL_LoadBMP(filePath.c_str());
	if (image != nullptr)
	{
		this->width = image->w;
		this->height = image->h;
		glGenTextures(1, &this->textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR,
			GL_UNSIGNED_BYTE, image->pixels);
	}
	SDL_FreeSurface(image);

	float vertices[4][4] =
	{
		{ 0.0f, 0.0f, 0.0f, 1.0f},
		{ width, 0.0f, 1.0f, 1.0f},
		{ 0.0f, height, 0.0f, 0.0f},
		{ width, height, 1.0f, 0.0f}
	};

	/* Allocate and assign a Vertex Array Object to our handle */
	glGenVertexArrays(1, &vao);
	/* Bind our Vertex Array Object as the current used object */
	glBindVertexArray(vao);

	/* Allocate and assign Vertex Buffer Objects to our handle */
	glGenBuffers(1, &vbo);

	/* vertices */
	/* Bind our first VBO as being the active buffer and storing vertex attributes (coordinates) */
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// TexCoord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Texture::setPosOffset(float x, float y)
{
	this->posOffsetX = x;
	this->posOffsetY = y;
}

void Texture::query(int* w, int* h)
{
	*w = width;
	*h = height;
}

void Texture::setRowsAndColumns(int rows, int columns)
{
	float vertices[4][4] =
	{
		{ 0.0f, 0.0f, 0.0f, 1.0f / rows},
		{ width / columns, 0.0f, 1.0f / columns, 1.0f / rows},
		{ 0.0f, height / rows, 0.0f, 0.0f},
		{ width / columns, height / rows, 1.0f / columns, 0.0f}
	};

	/* Allocate and assign a Vertex Array Object to our handle */
	glGenVertexArrays(1, &vao);
	/* Bind our Vertex Array Object as the current used object */
	glBindVertexArray(vao);

	/* Allocate and assign Vertex Buffer Objects to our handle */
	glGenBuffers(1, &vbo);

	/* vertices */
	/* Bind our first VBO as being the active buffer and storing vertex attributes (coordinates) */
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// TexCoord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Texture::queryWidthHeight(int* w, int* h)
{
	*w = this->width;
	*h = this->height;
}

void Texture::setOffset(float x, float y)
{
	this->offsetX = x;
	this->offsetY = y;
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

void Texture::draw(SceneViewer* v, Transform* transform /* = nullptr*/)
{
	if (transform)
	{
		glm::mat4 offset = translate(glm::mat4(1.0f), glm::vec3(posOffsetX, posOffsetY, 0.0f));
		glm::mat4 tempTransform = offset * transform->getGlmTransform();

		v->setModelMatrix(tempTransform);
	}

	glBindVertexArray(vao);
	v->setTexture(textureID, offsetX, offsetY);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Texture::setVertices(float sx, float sy, float sw, float sh)
{
	int w, h;
	queryWidthHeight(&w, &h);

	float leftX = sx / width;
	float topY = sy / height;
	float rightX = (sx + sw) / width;
	float bottomY = (sy + sh) / height;
	w = sw;
	h = sh;

	float vertices[4][4] =
	{
		{ 0.0f, 0.0f, leftX, topY},
		{ w, 0.0f, rightX, topY},
		{ 0.0f, h, leftX, bottomY},
		{ w, h, rightX, bottomY}
	};

	/* Allocate and assign a Vertex Array Object to our handle */
	glGenVertexArrays(1, &vao);
	/* Bind our Vertex Array Object as the current used object */
	glBindVertexArray(vao);

	/* Allocate and assign Vertex Buffer Objects to our handle */
	glGenBuffers(1, &vbo);

	/* vertices */
	/* Bind our first VBO as being the active buffer and storing vertex attributes (coordinates) */
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// TexCoord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
