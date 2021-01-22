#include "Texture.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "InitError.h"
#include "Renderer.h"
#include "Engine.h"

Texture::Texture(std::string filePath)
{
	// Load image from specified path
	SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
	if (surface == NULL)
		throw InitError();
	else
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
		texture = Engine::renderer->createTextureFromSurface(surface);
		if (texture == NULL)
			throw InitError();
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

	float vertices[4][5] =
	{
		{ 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
		{ width, 0.0f, 0.0f, 1.0f, 1.0f},
		{ 0.0f, height, 0.0f, 0.0f, 0.0f},
		{ width, height, 0.0f, 1.0f, 0.0f}
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// TexCoord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

Rect* Texture::getSrcRect()
{
	return srcRect;
}

Rect* Texture::getDstRect()
{
	return dstRect;
}

void Texture::setSrcRect(Rect newRect)
{
	srcRect->x = newRect.x;
	srcRect->y = newRect.y;
	srcRect->w = newRect.w;
	srcRect->h = newRect.h;
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
	// sets dstRect and keeps the texture offset
	dstRect->x = newRect.x + texOffsetX;
	dstRect->y = newRect.y + texOffsetY;
	dstRect->w = newRect.w;
	dstRect->h = newRect.h;
}

void Texture::setDstRect(int x, int y, int w, int h)
{
	// sets dstRect and keeps the texture offset
	dstRect->x = x + texOffsetX;
	dstRect->y = y + texOffsetY;
	dstRect->w = w;
	dstRect->h = h;
}

void Texture::setTexOffset(int x, int y)
{
	// remove the offset from the dstRect
	dstRect->x -= texOffsetX;
	dstRect->y -= texOffsetY;

	texOffsetX = x;
	texOffsetY = y;

	// add it back
	dstRect->x += texOffsetX;
	dstRect->y += texOffsetY;

	// this will make sure the offset is always applied
}

void Texture::query(int* w, int* h)
{
	SDL_QueryTexture(texture, NULL, NULL, w, h);
}

void Texture::setRowsAndColumns(int rows, int columns)
{
	float vertices[4][5] =
	{
		{ 0.0f, 0.0f, 0.0f, 0.0f, 1.0f / rows},
		{ width / columns, 0.0f, 0.0f, 1.0f / columns, 1.0f / rows},
		{ 0.0f, height / rows, 0.0f, 0.0f, 0.0f},
		{ width /columns, height / rows, 0.0f, 1.0f / columns, 0.0f}
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// TexCoord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Texture::queryWidthHeight(int* w, int* h)
{
	*w = this->width;
	*h = this->height;
}

void Texture::setOffset(int x, int y)
{
	this->offsetX = x;
	this->offsetY = y;
}

Texture::~Texture()
{
	delete srcRect;
	delete dstRect;
	SDL_DestroyTexture(texture);
}
